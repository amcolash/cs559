$(function () {
  var mySlider = $("input.slider").slider();
});

$('.slider').slider({
  formatter: function(value) {
    return 'Current value: ' + value;
  }
});

$('input').change(changeVal);

function changeVal() {
  alert($('#width').val());
  alert($('#height').val());
}

/* Code taken from svg-crowbar, found at https://nytimes.github.io/svg-crowbar */
function saveSvg() {
  var e = document.createElement('script');
  e.setAttribute('src', 'https://nytimes.github.io/svg-crowbar/svg-crowbar.js');
  e.setAttribute('class', 'svg-crowbar');
  document.body.appendChild(e);
}
