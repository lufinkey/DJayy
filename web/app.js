
var app = angular.module('DJayyApp', []);

app.controller('MainCtrl', ['$scope', function($scope) {
    
    $scope.tracks = [];

    $scope.addTrack = function(title, artist) {
        var track = {
            title: title,
            artist: artist
        };

        $scope.tracks.push(track);
        $scope.$apply();
    }
}]);
