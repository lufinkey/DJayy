
var app = angular.module('DJayyApp', []);

app.controller('MainCtrl', ['$scope', '$timeout', '$http', function($scope, $timeout, $http) {
    
    //Scope variables
    $scope.tracks = [];

    //Local variables
    var tracksToSend = [];

    //Scope functions
    $scope.addTrack = function(title, artist) {
        var track = {
            title: title,
            artist: artist,
            userVote: 1
        };

        sendTracks.push(track);
    };
    
    //Local functions
    var serverPoll = function() {
        $timeout(function() {
            getTrackList("tracks.json");
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
        
        tracksToSend = [];
    };

    serverPoll();
}]);
