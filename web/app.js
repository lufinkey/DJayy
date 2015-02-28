
var app = angular.module('DJayyApp', ['ngCookies']);

app.controller('MainCtrl', ['$scope', '$timeout', '$http', '$cookies', '$cookieStore', function($scope, $timeout, $http, $cookies, $cookieStore) {
    
    if (typeof $cookieStore.get('djayy_user_id') == 'undefined')
        $cookieStore.put('djayy_user_id', client_get_user_id());
    
    //Scope variables
    $scope.queue = [];

    //Local variables
    var user_id = $cookieStore.get('djayy_user_id');
    var first_connect = true;

    //Scope functions
    $scope.server_trackVote = function(event, queue_id, vote) {
        $http.post("/queuevote", {user_id: user_id, queue_id: queue_id, vote: vote}).then(function(response) {
            var update_track = client_findTrackByQ_Id(response.data.queue_id);
            var button = angular.element(event.sourceElement);

            if (response.data.vote == 0) {
                    button.removeClass("active");
                if (button.attr("id") == "up") {
                    button.next().removeClass("active");
                } else {
                    button.prev().removeClass("active");
                }
            } else if (response.data.vote == 1) {
                button.addClass("active");
                button.next().removeClass("active");
            } else if (response.data.vote == -1) {
                //only downvote button is highlighted
                button.addClass("active");
                button.prev().removeClass("active");
            }

            update_track.votes = response.data.totalVotes;
        });
    };
    
    //Local functions
    function server_poll() {
        $timeout(function() {
            if (first_connect) {
                server_getQueue();
                first_connect = false;
            }
            
            server_poll();
        }, 1000);
    };

    function server_getQueue() {
        $http.get("/queue").then(function(response) {
            $scope.queue = response.data.queue;
        });
    };

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
