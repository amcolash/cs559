$(function () {
  genCode();
});

$('input').change(changeVal);

function changeVal() {
  var height = $('#heightRange').val();
  var width = $('#widthRange').val();
  $('#svgImage #box').attr("width", width);
  $('#svgImage #box').attr("height", height);
  genCode();
}

function genCode() {
  var svg = $('#svgImage')[0];
  var svg_xml = (new XMLSerializer).serializeToString(svg);
  svg_xml = vkbeautify.xml(svg_xml);
  $('#svgCode').text(svg_xml);
  $('#svgCode').removeClass('prettyprinted');
  prettyPrint();
}

function reset() {
  $('#heightValue').val('100');
  $('#widthValue').val('100');
  $('#heightRange').val('100');
  $('#widthRange').val('100');
  changeVal();
}

/* Code taken from svg-crowbar, found at https://nytimes.github.io/svg-crowbar */
function saveSvg() {
  var e = document.createElement('script');
  e.setAttribute('src', 'https://nytimes.github.io/svg-crowbar/svg-crowbar.js');
  e.setAttribute('class', 'svg-crowbar');
  document.body.appendChild(e);
}
