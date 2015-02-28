
var app = angular.module('DJayyApp', ['ngCookies']);

app.controller('MainCtrl', ['$scope', '$timeout', '$http', '$cookies', '$cookieStore',
        function($scope, $timeout, $http, $cookies, $cookieStore) {
    
    //Scope variables
    $scope.queue = [];
    $scope.search = [];

    $scope.queue_page_start = 0;
    $scope.search_page_start = 0;

    //Local variables
    if (typeof $cookieStore.get('djayy_user_id') == 'undefined')
        $cookieStore.put('djayy_user_id', client_get_user_id());
    
    var user_id = $cookieStore.get('djayy_user_id');
    var first_connect = true;

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

    $scope.client_moveQueuePage = function(amt) {
        $scope.queue_page_start += amt;
    }

    $scope.client_queueRange = function() {
        range = [];

        for (i = $scope.queue_page_start; i < $scope.queue_page_start + 9; i++) {
            if (i > $scope.queue.length)
                return range;

            range.push(i);
        }

        return range;
    }

    $scope.client_queueCanMoveBack = function() {
        return ($scope.queue_page_start - 10) > 0;
    }

    $scope.client_queueCanMoveForward = function() {
        return ($scope.queue_page_start + 10) < ($scope.queue_page_start + $scope.queue_page_start % 10);
    }

    //Local functions
    function server_poll() {
        $timeout(function() {
            if (first_connect) {
                server_getQueue(0, 0);
                first_connect = false;
            }

            server_poll();
        }, 1000);
    };
   
    function server_getQueue(minEntry, maxEntry) {
        $http.post("/queue", {minEntry: minEntry, maxEntry: maxEntry}).then(function(response) {
            $scope.queue = $scope.queue.concat(response.data);
            $scope.client_advanceQueuePage('none');    
        });
    };

    function server_search(query, minEntry, maxEntry) {
        $http.post("/search", {query: query, minEntry: minEntry, maxEntry: maxEntry}).then(function(response) {
            $scope.search = $scope.query.concat(response.data);
        });
    }

    function client_findTrackByQ_Id(queue_id) {
        for (i = 0; i < $scope.queue.length; i++) {
            if ($scope.queue[i].queue_id == queue_id)
                return $scope.queue[i];
        }
    };

    function client_get_user_id() {
        return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
            var r = Math.random()*16|0, v = c === 'x' ? r : (r&0x3|0x8);
            return v.toString(16);
        });
    };


    server_poll();
        }]);
