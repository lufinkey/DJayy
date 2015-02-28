
var app = angular.module('DJayyApp', []);

app.controller('MainCtrl', ['$scope', '$timeout', '$http', function($scope, $timeout, $http) {
    
    //Scope variables
    $scope.tracks = [];

    //Local variables
    var tracksToSend = [];

    //Scope functions
    $scope.addTrack = function(id, uservote) {
        var track = {
            id: id,
            userVote: uservote 
        };

        tracksToSend.push(track);
    };

    $scope.trackVote = function(id, vote) {
        findTrackById(id).vote += vote;
        $scope.addTrack(id, vote);
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

    var findTrackById = function(id) {
        for (i = 0; i < $scope.tracks.length; i++) {
            if ($scope.tracks[i].id == id)
                return $scope.tracks[i];
        }
    };

    serverPoll();
}]);
