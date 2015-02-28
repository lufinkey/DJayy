
var app = angular.module('DJayyApp', []);

app.controller('MainCtrl', ['$scope', '$timeout', '$http', function($scope, $timeout, $http) {
    
    //Scope variables
    $scope.tracks = [];

    //Local variables
    var tracksToSend = [];

    //Scope functions
    $scope.addTrack = function(id, uservote) {
        var track = {
            track_id: track_id,
            userVote: uservote 
        };

        tracksToSend.push(track);
    };

    $scope.trackVote = function(track_id, vote) {
        findTrackByTrackId(track_id).vote += vote;
        $scope.addTrack(track_id, vote);
    };
    
    //Local functions
    var serverPoll = function() {
        $timeout(function() {
            getTrackList("/queue");
            sendTracks(tracksToSend);

            serverPoll();
        }, 1000);
    };

    var getTrackList = function(trackJSON) {
        $http.get(trackJSON).then(function(response) {
            $scope.tracks = response.data.tracks;
        });
    };

    var sendTracks = function(tracks) {
        //Send the files to the server
        var tracksAsJson = JSON.stringify(tracks);
    };

    var findTrackByTrackId = function(track_id) {
        for (i = 0; i < $scope.tracks.length; i++) {
            if ($scope.tracks[i].track_id == track_id)
                return $scope.tracks[i];
        }
    };

    serverPoll();
}]);
