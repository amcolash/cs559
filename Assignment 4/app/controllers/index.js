import Ember from 'ember';
//import prettyPrint from 'prettyPrint';
//import vkbeautify from 'vkbeautify';

export default Ember.Controller.extend({

  code : '',

  height : 250,
  width : 250,

  line : {
    x1 : 50,
    y1 : 100,
    z1 : 30,
    x2 : 150,
    y2 : 90,
    z2 : 220
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
  
  lines : [[50,50,0,50,300,0], [50,50,0,300,50,0], [50,300,0,300,300,0], [300,50,0,300,300,0]],

  finalLines : function() {
    console.log("lines changed");
    var temp = [[]];
    var lines = this.get('lines');

    for (var i = 0; i < lines.length; i++) {
      temp[i] = [ lines[i][0], lines[i][1], lines[i][3], lines[i][4] ];
    }

    return temp;
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

      var point = new Matrix( [5,0,0,0, 0,5,0,0, 0,0,1,0, 0,0,0,0] );

      temp = point.multiply(temp);
      console.log("-------------------------------");
      console.log("[" + temp.m[0] + ", " + temp.m[1] + ", " + temp.m[2] + ", " + temp.m[3] + "]");
      console.log("[" + temp.m[4] + ", " + temp.m[5] + ", " + temp.m[6] + ", " + temp.m[7] + "]");
      console.log("[" + temp.m[8] + ", " + temp.m[9] + ", " + temp.m[10] + ", " + temp.m[11] + "]");
      console.log("[" + temp.m[12] + ", " + temp.m[13] + ", " + temp.m[14] + ", " + temp.m[15] + "]");
    },

    add : function() {
      var temp = [[]];
      var lines = this.get('lines');
      for (var i = 0; i < lines.length; i++) {
        temp[i] = [ lines[i][0], lines[i][1], lines[i][2], lines[i][3], lines[i][4], lines[i][5] ];
      }

      temp[i] = [ this.get('line.x1'), this.get('line.y1'), this.get('line.z1'), this.get('line.x2'), this.get('line.y2'), this.get('line.z2') ];
      this.set('lines', temp);
      //console.log(lines);
      //console.log(this.get('lines'));
    },

    codeGen : function() {
      var svg = $('#svgImage')[0];
      var svg_xml = (new XMLSerializer ()).serializeToString(svg);
      svg_xml = svg_xml.replace(/<script.*>/g, "");
      svg_xml = svg_xml.replace(/data-bindattr-[0-9]*="[0-9]*" /g, "");
      console.log(svg_xml);
      this.set('code', svg_xml);
      svg_xml = vkbeautify.xml(svg_xml);
      $('#svgCode').text(svg_xml);
      $('#svgCode').removeClass('prettyprinted');
      prettyPrint();
    },

    remove : function(element) {
      var temp = [[]];
      var lines = this.get('lines');
      var index = lines.indexOf(element);
      if (index > -1) {
        // Make a copy of the array to manipulate, ember gets grumpy otherwise
        for (var i = 0; i < lines.length; i++) {
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
      this.send('codeGen');
      var fileName = "svgImge.svg";

      saveData(this.get('code'), fileName);
    }
  }

 
});