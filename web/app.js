
var app = angular.module('DJayyApp', ['ngCookies']);

app.controller('MainCtrl', ['$scope', '$timeout', '$http', '$cookieStore', function($scope, $timeout, $http, $cookieStore) {

    if (typeof $cookieStore.get('djayy_user_id') != 'undefined') {
        $cookieStore.set('djayy_user_id', client_user_idVal());
    }

    //Scope variables
    $scope.queue = [];

    //Local variables
    var user_id = $cookieStore.put('djayy_user_id');
    var first_connect = true;

    //Scope functions
    $scope.server_trackVote = function(event, q_id, vote) {
        $http.post("/queuevote", {user_id: user_id, q_id: q_id, vote: vote}}).then(function(response) {
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

            serverPoll();
        }, 1000);
    };

    var server_getQueue = function() {
        $http.get(trackJSON).then(function(response) {
            $scope.queue = response.data.queue;
        });
    };

    var client_findTrackByQ_Id = function(q_id) {
        for (i = 0; i < $scope.queue.length; i++) {
            if ($scope.queue[i].q_id == q_id)
                return $scope.queue[i];
        }
    };

    var client_user_idVal = function() {
        function s4() {
            return Math.floor((1 + Math.random()) * 0x10000)
                .toString(16).substring(1);
        }
        
        return s4() + s4() + '-' + s4() + '-' + s4() + '-' + 
            s4() + '-' + s4() + s4() + s4();
    };

    serverPoll();
}]);
