import Ember from 'ember';
//import prettyPrint from 'prettyPrint';
//import vkbeautify from 'vkbeautify';

export default Ember.Controller.extend({

  height : 250,
  width : 250,

  line : {
    x1 : 0,
    y1 : 0,
    z1 : 0,
    x2 : 0,
    y2 : 0,
    z2 : 0,
  },

  perspective : {
    ex : 0,
    ey : 0,
    ez : -1,
    cx : 0,
    cy : 0,
    cz : 0,
    ux : 0,
    uy : 1,
    uz : 0
  },
  
  lines : [[2,3,9,0,4,2], [1,-1,-8,2,6,5], [7,1,-1,6,2,5]],
  //finalLines : [[50,20,90,150]],
  finalLines : function() {

  }.property('lines'),

  actions: {

    test : function() {
      //console.log(lookAt(ex, ey, ez, cx, cy, cz, ux, uy, uz));

      // console.log(this.get('perspective.ex'));
      // console.log(this.get('perspective.ey'));
      // console.log(this.get('perspective.ez'));
      // console.log(this.get('perspective.cx'));
      // console.log(this.get('perspective.cy'));
      // console.log(this.get('perspective.cz'));
      // console.log(this.get('perspective.ux'));
      // console.log(this.get('perspective.uy'));
      // console.log(this.get('perspective.uz'));

      var temp = Matrix.lookAt(this.get('perspective.ex'), this.get('perspective.ey'), this.get('perspective.ez'), this.get('perspective.cx'), this.get('perspective.cy'),
                               this.get('perspective.cz'), this.get('perspective.ux'), this.get('perspective.uy'), this.get('perspective.uz'));

      console.log("-------------------------------");
      console.log("[" + temp.m[0] + ", " + temp.m[1] + ", " + temp.m[2] + ", " + temp.m[3] + "]");
      console.log("[" + temp.m[4] + ", " + temp.m[5] + ", " + temp.m[6] + ", " + temp.m[7] + "]");
      console.log("[" + temp.m[8] + ", " + temp.m[9] + ", " + temp.m[10] + ", " + temp.m[11] + "]");
      console.log("[" + temp.m[12] + ", " + temp.m[13] + ", " + temp.m[14] + ", " + temp.m[15] + "]");

      point = Matrix(5,0,0,0
                     0,5,0,0
                     0,0,1,0
                     0,0,0,0);

      temp = temp.Multiply(temp);
      console.log("-------------------------------");
      console.log("[" + temp.m[0] + ", " + temp.m[1] + ", " + temp.m[2] + ", " + temp.m[3] + "]");
      console.log("[" + temp.m[4] + ", " + temp.m[5] + ", " + temp.m[6] + ", " + temp.m[7] + "]");
      console.log("[" + temp.m[8] + ", " + temp.m[9] + ", " + temp.m[10] + ", " + temp.m[11] + "]");
      console.log("[" + temp.m[12] + ", " + temp.m[13] + ", " + temp.m[14] + ", " + temp.m[15] + "]");
    },

    add : function() {
      var lines = this.get('lines');
      lines.pushObject([ this.get('line.x1'), this.get('line.y1'), this.get('line.z1'), this.get('line.x2'), this.get('line.y2'), this.get('line.z2') ]);
      this.set('lines', lines);
      console.log(lines);
      console.log(this.get('lines'));
    },

    codeGen : function() {
      var svg = $('#svgImage')[0];
      var svg_xml = (new XMLSerializer ()).serializeToString(svg);
      svg_xml = svg_xml.replace(/<script.*>/g, "");
      svg_xml = svg_xml.replace(/data-bindattr-[0-9]*="[0-9]*" /g, "");
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

      this.set('line.x1', 0);
      this.set('line.y1', 0);
      this.set('line.z1', 0);
      this.set('line.x2', 0);
      this.set('line.y2', 0);
      this.set('line.z2', 0);
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