
var app = angular.module('DJayyApp', ['ngCookies', 'infinite-scroll']);

app.controller('MainCtrl', ['$scope', '$timeout', '$http', '$cookies', '$cookieStore',
        function($scope, $timeout, $http, $cookies, $cookieStore) {
    
    //Scope variables
    $scope.queue = [];
    $scope.search = [];
    $scope.nowplaying = [];
    $scope.album_src = "";

    $scope.queue_page_start = 0;
    $scope.search_page_start = 0;
    $scope.queue_page_length = 10;
    $scope.search_page_length = 10;

    //Local variables
    if (typeof $cookieStore.get('djayy_user_id') == 'undefined')
        $cookieStore.put('djayy_user_id', client_get_user_id());
    
    var user_id = $cookieStore.get('djayy_user_id');
    var lastfm_api_key = "ddd30b65f917c285ea5fb4ace276815d";

    //Scope functions
    $scope.server_trackVote = function($event, queue_id, vote) {
        $http.post("/queuevote", {user_id: user_id, queue_id: queue_id, vote: vote}).then(function(response) {
            var update_track = client_findTrackByQ_Id(response.data.queue_id);
            var button = angular.element($event.target);

            //Manually toggle buttons
            if (response.data.vote == 0) {
                    $(button).removeClass("active");
                if ($(button).attr("id") == "up") {
                    $(button).next().removeClass("active");
                } else {
                    $(button).prev().removeClass("active");
                }
            } else if (response.data.vote == 1) {
                $(button).addClass("active");
                $(button).next().removeClass("active");
            } else if (response.data.vote == -1) {
                $(button).addClass("active");
                $(button).prev().removeClass("active");
            }

            update_track.votes = response.data.totalVotes;
        });
    };
    
    $scope.client_loadMore = function(query) {

        if ($scope.search_page_start != 0) {
            $http.post("/search", {query: query, minEntry: $scope.search_page_start, maxEntry: $scope.search_page_start
                + $scope.search_page_length}).then(function(response) {
                    $scope.search = $scope.search.concat(response.data);
                });
        }
        
        $scope.search_page_start += $scope.search_page_length;
    };

    $scope.server_search = function(query) {
        $scope.search_page_start = 0;

        $http.post("/search", {query: query, minEntry: $scope.search_page_start, maxEntry: $scope.search_page_start
            + $scope.search_page_length}).then(function(response) {
                $scope.search = response.data;
            });
    };

    $scope.client_moveQueuePage = function(amt) {
        $scope.queue_page_start += amt;
    };

    $scope.client_queueRange = function() {
        range = [];

        for (i = $scope.queue_page_start; i < $scope.queue_page_start + 9; i++) {
            if (i >= $scope.queue.length)
                return range;

            range.push(i);
        }

        return range;
    };

    $scope.client_queueCanMoveBack = function() {
        return ($scope.queue_page_start) > 0;
    };

    $scope.client_queueCanMoveForward = function() {
        return ($scope.queue_page_start + $scope.queue_page_length) < $scope.queue.length;
    };

    $scope.server_addToQueue = function(track) {
        $http.post("/addqueue", {track_id: track.track_id, user_id: user_id}).then(function(response) {
            //get back the q_id and add modularly
        });
    };

    //Local functions
    function queue_poll() {
        $timeout(function() {
            server_getQueue(0, 0);

            queue_poll();
        }, 1000);
    }

    function nowplaying_poll() {
        $timeout(function() {
            server_getNowPlaying();

            nowplaying_poll();
        }, 5000);    
    }

    function server_getQueue(minEntry, maxEntry) {
        $http.post("/queue", {minEntry: minEntry, maxEntry: maxEntry}).then(function(response) {
            $scope.queue = response.data;
        });
    }

    function server_getNowPlaying() {
        $http.get("/nowplaying").then(function(response) {
            if (response.data.status) {

                if (response.data.track != $scope.nowplaying) {
                    client_getAlbumArtwork(response.data.track);
                }

                $scope.nowplaying = response.data.track;
            } else {
                $scope.nowplaying = [];
            }
        });
    }
    
    function client_getAlbumArtwork(track) {
        $http.get("http://ws.audioscrobbler.com/2.0/?method=album.getinfo&api_key=" + lastfm_api_key + "&artist="
                + track.artist + "&album=" + track.album + "&format=json").then(function(response) {
                    var images = response.data.image;

                    $scope.album_src = images[images.length - 1]["#text"];
                    console.log($scope.album_src);
        });
    }

    function client_findTrackByQ_Id(queue_id) {
        for (i = 0; i < $scope.queue.length; i++) {
            if ($scope.queue[i].queue_id == queue_id)
                return $scope.queue[i];
        }
    }

    function client_get_user_id() {
        return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
            var r = Math.random()*16|0, v = c === 'x' ? r : (r&0x3|0x8);
            return v.toString(16);
        });
    }

    queue_poll();
    nowplaying_poll();
        }]);
