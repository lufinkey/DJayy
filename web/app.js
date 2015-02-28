
var app = angular.module('DJayyApp', ['ngCookies']);

app.controller('MainCtrl', ['$scope', '$timeout', '$http', '$cookies', '$cookieStore', function($scope, $timeout, $http, $cookies, $cookieStore) {
    
    var client_get_user_id = function() {
        return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
            var r = Math.random()*16|0, v = c === 'x' ? r : (r&0x3|0x8);
            return v.toString(16);
        });
    };

    if (typeof $cookieStore.get('djayy_user_id') == 'undefined')
        $cookieStore.put('djayy_user_id', client_get_user_id());
    
    //Scope variables
    $scope.queue = [];

    //Local variables
    var user_id = $cookieStore.get('djayy_user_id');
    var first_connect = true;

    //Scope functions
    $scope.server_trackVote = function(event, q_id, vote) {
        $http.post("/queuevote", {user_id: user_id, q_id: q_id, vote: vote}).then(function(response) {
            var update_track = client_findTrackByQ_Id(response.data.q_id);
            var button = angular.element(event.sourceElement);

            //TODO handle vote toggling

            update_track.votes = response.data.totalVotes;
        });
    };
    
    //Local functions
    var server_poll = function() {
        $timeout(function() {
            if (first_connect) {
                server_getQueue();
                first_connect = false;
            }
            
            server_poll();
        }, 1000);
    };

    var server_getQueue = function() {
        $http.get("queue.json").then(function(response) {
            $scope.queue = response.data.queue;
        });
    };

    var client_findTrackByQ_Id = function(q_id) {
        for (i = 0; i < $scope.queue.length; i++) {
            if ($scope.queue[i].q_id == q_id)
                return $scope.queue[i];
        }
    };


    server_poll();
}]);
