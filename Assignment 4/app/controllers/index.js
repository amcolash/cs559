import Ember from 'ember';
import prettyPrint from 'prettyPrint';
import vkbeautify from 'vkbeautify';

export default Ember.Controller.extend({

  height : 250,
  width : 250,

  tempx1 : 0,
  tempy1 : 0,
  tempz1 : 0,
  tempx2 : 0,
  tempy2 : 0,
  tempz2 : 0,
  
  lines : [[2,3,9,0,4,2], [1,-1,-8,2,6,5], [7,1,-1,6,2,5]],
  finalLines : [[]],

  actions: {
    add : function() {
      var lines = this.get('lines');
      lines.pushObject([ this.get('tempx1'), this.get('tempy1'), this.get('tempz1'), this.get('tempx2'), this.get('tempy2'), this.get('tempz2') ]);
      this.set('lines', lines);
      console.log(lines);
      console.log(this.get('lines'));
    },

    codeGen : function() {
      var svg = $('#svgImage')[0];
      var svg_xml = (new XMLSerializer ()).serializeToString(svg);
      svg_xml = vkbeautify.xml(svg_xml);
      $('#svgCode').text(svg_xml);
      $('#svgCode').removeClass('prettyprinted');
      prettyPrint();
    },

    remove : function(element) {
      var i = 0;
      var temp = [[]];
      var lines = this.get('lines');
      var index = lines.indexOf(element);
      if (index > -1) {
        // Make a copy of the array to manipulate, ember gets grumpy otherwise
        for (i = 0; i < lines.length; i++) {
          temp[i] = lines[i];
        }
        temp.splice(index, 1);
      }
      this.set('lines', temp);
    },

    reset : function() {
      this.set('height', 250);
      this.set('width', 250);

      this.set('tempx1', 0);
      this.set('tempy1', 0);
      this.set('tempz1', 0);
      this.set('tempx2', 0);
      this.set('tempy2', 0);
      this.set('tempz2', 0);
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