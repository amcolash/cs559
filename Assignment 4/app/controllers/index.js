import Ember from 'ember';

export default Ember.Controller.extend({

  height : 250,
  width : 250,

  tempx1 : 0,
  tempy1 : 0,
  tempx2 : 0,
  tempy2 : 0,
  
  lines : [[2,3,4,2], [1,2,6,5], [7,1,6,5]],

  actions: {
    codeGen : function() {
      var svg = $('#svgImage')[0];
      var svg_xml = (new XMLSerializer).serializeToString(svg);
      svg_xml = vkbeautify.xml(svg_xml);
      $('#svgCode').text(svg_xml);
      $('#svgCode').removeClass('prettyprinted');
      prettyPrint();
    },

    remove : function(element) {
      var lines = this.get('lines');
      var index = lines.indexOf(element);
      if (index > -1) {
        console.log("Removing item " + index + " from the array");
      }
      this.set('lines', lines);
      console.log(this.get('lines'));
    },

    reset : function() {
      this.set('height', 100);
      this.set('width', 100);

      this.set('tempx1', 0);
      this.set('tempy1', 0);
      this.set('tempx2', 0);
      this.set('tempy2', 0);
    },

    save : function() {
      /* Code taken from svg-crowbar, found at https://nytimes.github.io/svg-crowbar */
      var e = document.createElement('script');
      e.setAttribute('src', 'https://nytimes.github.io/svg-crowbar/svg-crowbar.js');
      e.setAttribute('class', 'svg-crowbar');
      document.body.appendChild(e);
    }
  }

 
});