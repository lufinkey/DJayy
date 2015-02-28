
var app = angular.module('DJayyApp', []);

app.controller('MainCtrl', ['$scope', '$timeout', '$http', function($scope, $timeout, $http) {
    
    $scope.tracks = [];

    var serverPoll = function() {
        $timeout(function() {
            getTrackList("tracks.json");

            serverPoll();
        }, 1000);
    };

    var getTrackList = function(trackJSON) {
        $http.get(trackJSON).then(function(response) {
            $scope.tracks = response.data.tracks;
            $scope.$apply();
        });
    };

    var addTrack = function(title, artist) {
        var track = {
            title: title,
            artist: artist,
            votes: 0
        };

        $scope.tracks.push(track);
        $scope.$apply();
    };

    serverPoll();
}]);
