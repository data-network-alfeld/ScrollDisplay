#pragma once

const char* animationStartHTML = "<label for='animationStart'>Animation Start</label><br/>\
<select name='animationStart' id='animationStart' style='border-radius: .3rem;width: 100%; padding: 5px;font-size: 1em;margin: 5px 0; box-sizing: border-box;' onchange=\"if (this.selectedIndex==6){document.getElementById('spriteStartBlock').style.display = 'block'} else {document.getElementById('spriteStartBlock').style.display = 'none'}\")>\
<option value='0'>PA_NO_EFFECT</option>\
<option value='1'>PA_PRINT</option>\
<option value='2'>PA_SCROLL_UP</option>\
<option value='3'>PA_SCROLL_DOWN</option>\
<option value='4' selected>PA_SCROLL_LEFT</option>\
<option value='5'>PA_SCROLL_RIGHT</option>\
<option value='6'>PA_SPRITE</option>\
<option value='7'>PA_SLICE</option>\
<option value='8'>PA_MESH</option>\
<option value='9'>PA_FADE</option>\
<option value='10'>PA_DISSOLVE</option>\
<option value='11'>PA_BLINDS</option>\
<option value='12'>PA_RANDOM</option>\
<option value='13'>PA_WIPE</option>\
<option value='14'>PA_WIPE_CURSOR</option>\
<option value='15'>PA_SCAN_HORIZ</option>\
<option value='16'>PA_SCAN_HORIZX</option>\
<option value='17'>PA_SCAN_VERT</option>\
<option value='18'>PA_SCAN_VERTX</option>\
<option value='19'>PA_OPENING</option>\
<option value='20'>PA_OPENING_CURSOR</option>\
<option value='21'>PA_CLOSING</option>\
<option value='22'>PA_CLOSING_CURSOR</option>\
<option value='23'>PA_SCROLL_UP_LEFT</option>\
<option value='24'>PA_SCROLL_UP_RIGHT</option>\
<option value='25'>PA_SCROLL_DOWN_LEFT</option>\
<option value='26'>PA_SCROLL_DOWN_RIGHT</option>\
<option value='27'>PA_GROW_UP</option>\
<option value='28'>PA_GROW_DOWN</option>\
</select><br>";

const char* animationEndeHTML = "<label for='animationEnde'>Animation Ende</label><br/>\
<select name='animationEnde' id='animationEnde' style='border-radius: .3rem;width: 100%; padding: 5px;font-size: 1em;margin: 5px 0; box-sizing: border-box;' onchange=\"if (this.selectedIndex==6){document.getElementById('spriteEndeBlock').style.display = 'block'} else {document.getElementById('spriteEndeBlock').style.display = 'none'}\")>\
<option value='0'>PA_NO_EFFECT</option>\
<option value='1'>PA_PRINT</option>\
<option value='2'>PA_SCROLL_UP</option>\
<option value='3'>PA_SCROLL_DOWN</option>\
<option value='4' selected>PA_SCROLL_LEFT</option>\
<option value='5'>PA_SCROLL_RIGHT</option>\
<option value='6'>PA_SPRITE</option>\
<option value='7'>PA_SLICE</option>\
<option value='8'>PA_MESH</option>\
<option value='9'>PA_FADE</option>\
<option value='10'>PA_DISSOLVE</option>\
<option value='11'>PA_BLINDS</option>\
<option value='12'>PA_RANDOM</option>\
<option value='13'>PA_WIPE</option>\
<option value='14'>PA_WIPE_CURSOR</option>\
<option value='15'>PA_SCAN_HORIZ</option>\
<option value='16'>PA_SCAN_HORIZX</option>\
<option value='17'>PA_SCAN_VERT</option>\
<option value='18'>PA_SCAN_VERTX</option>\
<option value='19'>PA_OPENING</option>\
<option value='20'>PA_OPENING_CURSOR</option>\
<option value='21'>PA_CLOSING</option>\
<option value='22'>PA_CLOSING_CURSOR</option>\
<option value='23'>PA_SCROLL_UP_LEFT</option>\
<option value='24'>PA_SCROLL_UP_RIGHT</option>\
<option value='25'>PA_SCROLL_DOWN_LEFT</option>\
<option value='26'>PA_SCROLL_DOWN_RIGHT</option>\
<option value='27'>PA_GROW_UP</option>\
<option value='28'>PA_GROW_DOWN</option>\
</select><br>";

const char* spriteStartHTML = "<span id='spriteStartBlock' style='display: none'><label for='spriteStart'>Sprite Start</label><br/>\
<select name='spriteStart' id='spriteStart' style='border-radius: .3rem;width: 100%; padding: 5px;font-size: 1em;margin: 5px 0; box-sizing: border-box;'>\
<option value='0' selected>Pacman</option>\
<option value='1'>Pacman und Geist</option>\
<option value='2'>Rocket</option>\
<option value='3'>Invader</option>\
<option value='4'>Chevron</option>\
<option value='5'>Heart</option>\
<option value='6'>Steamboat</option>\
<option value='7'>Sailboat</option>\
<option value='8'>Fireball</option>\
<option value='9'>Roll1</option>\
<option value='10'>Roll2</option>\
<option value='11'>Arrow1</option>\
<option value='12'>Arrow2</option>\
<option value='13'>Wave</option>\
<option value='14'>Lines</option>\
</select><br> \
<canvas id='spriteStartCanvas' width='200' height='100' style='border:1px solid #d3d3d3;'>\
Your browser does not support the HTML5 canvas tag.</canvas></span>";

const char* spriteEndeHTML = "<span id='spriteEndeBlock' style='display: none'><label for='spriteEnde'>Sprite Ende</label><br/>\
<select name='spriteEnde' id='spriteEnde' style='border-radius: .3rem;width: 100%; padding: 5px;font-size: 1em;margin: 5px 0; box-sizing: border-box;'>\
<option value='0' selected>Pacman</option>\
<option value='1'>Pacman und Geist</option>\
<option value='2'>Rocket</option>\
<option value='3'>Invader</option>\
<option value='4'>Chevron</option>\
<option value='5'>Heart</option>\
<option value='6'>Steamboat</option>\
<option value='7'>Sailboat</option>\
<option value='8'>Fireball</option>\
<option value='9'>Roll1</option>\
<option value='10'>Roll2</option>\
<option value='11'>Arrow1</option>\
<option value='12'>Arrow2</option>\
<option value='13'>Wave</option>\
<option value='14'>Lines</option>\
</select><br>\
<canvas id='spriteEndeCanvas' width='200' height='100' style='border:1px solid #d3d3d3;'>\
Your browser does not support the HTML5 canvas tag.</canvas></span>\
<script>\
var animationnr = [0,0];\
var x = [10,10];\
var y = [80,80];\
var warte = [0,0];\
var sprite = [0,0];\
var hex_ani = [0,0];\
var requestID = [undefined,undefined];\
\
\
var allesprites = [['pacman1',6,8,'0081c3e7ff7e7e3c0042e7e7ffff7e3c2466e7ffffff7e3c3c7effffffff7e3c2466e7ffffff7e3c0042e7e7ffff7e3c'],['pacman2',6,18,'0081c3e7ff7e7e3c000000fe7bf37ffb73fe0042e7e7ffff7e3c000000fe7bf37ffb73fe2466e7ffffff7e3c000000fe7bf37ffb73fe3c7effffffff7e3c000000fe7bf37ffb73fe2466e7ffffff7e3c000000fe7bf37ffb73fe0042e7e7ffff7e3c000000fe7bf37ffb73fe'],['rocket',2,11,'1824428199189918a55a811824428118991899244299'],['invader',2,10,'0e987d363c3c367d980e70187db63c3cb67d1870'],['chevron',1,9,'183c66c3993c66c381'],['heart',5,9,'0e112142844221110e0e1f3366cc66331f0e0e1f3f7efc7e3f1f0e0e1f3366cc66331f0e0e112142844221110e'],['steamboat',2,11,'1030509c9e90919c9d90711030509c9c91909d9e9170'],['sailboat',1,11,'10305894929f9294985030'],['fireball',2,11,'7eab5428522440180410087ed52a14240a3004280810'],['roll1',4,8,'ff8f8f8f818181fffff1f1f1818181ffff818181f1f1f1ffff8181818f8f8fff'],['roll2',4,8,'3c4e8f8f8181423c3c72f1f18181423c3c428181f1f1723c3c4281818f8f4e3c'],['arrow1',3,10,'183c7eff7e00003c0000183c7eff007e00001800183c7eff00003c000018'],['arrow2',3,9,'183c7ee70000c30000183c7ee7e700008100183c7ee700c3000081'],['wave',14,14,'08040201020408102040804020101008040201020408102040804020201008040201020408102040804040201008040201020408102040808040201008040201020408102040408040201008040201020408102020408040201008040201020408101020408040201008040201020408081020408040201008040201020404081020408040201008040201020204081020408040201008040201010204081020408040201008040202010204081020408040201008040402010204081020408040201008'],['lines',3,8,'ffffff0000ff0000ffff00ff0000ff00ffff0000ff0000ff']];\
\
  var selStart = document.getElementById('spriteStart');\
  selStart.onchange = function(){spritewechsel(this.value,0)};\
  var selEnde = document.getElementById('spriteEnde');\
  selEnde.onchange = function(){spritewechsel(this.value,1)};\
\
  spritewechsel(0,0);\
  spritewechsel(0,1);\
\
function spritewechsel (element,zustand)  {\
    animationnr[zustand] = 0;\
    x[zustand] = 10;\
    y[zustand] = 80;\
    if (requestID[zustand]) {\
      cancelAnimationFrame(requestID[zustand]);\
      requestID[zustand] = undefined;\
    } \
    sprite[zustand] = allesprites[element];\
    var splitten = '.{1,'+ 2*sprite[zustand][2] + '}';\
    var re = new RegExp(splitten, 'g');\
    hex_ani[zustand] = sprite[zustand][3].match(re);\
    if (zustand == 0) {\
        animate0();\
    }\
    if (zustand == 1) {\
        animate1();\
    }\
  }\
\
function animate0 () {\
    requestID[0] = requestAnimationFrame(animate0);\
    render0(); \
}\
function animate1 () {\
    requestID[1] = requestAnimationFrame(animate1);\
    render1(); \
}\
\
function render0 () {\
    var c = document.getElementById('spriteStartCanvas');\
    var ctx = c.getContext('2d');\
    ctx.fillStyle = '#FF0000';\
    ctx.clearRect(0, 0, 200, 100);\
    x[0] = 10;\
    y[0] = 80;\
    var hex = hex_ani[0][animationnr[0]].match(/.{1,2}/g);\
    var bin;\
    for (h = 0; h < hex.length; h++) {\
       bin = hex2bin(hex[h]).split('');\
       for (i = 0; i < bin.length; i++) {\
        \
        if (bin[i]==1) {\
          ctx.fillRect(x[0],y[0],10,10);\
        } else {\
          ctx.fillRect(x[0],y[0],0,0);\
        }\
        y[0]-=10;\
      }\
      x[0]+=10;\
      y[0]=80;\
    }\
    ctx.stroke();\
    warte[0]++;\
    if (warte[0] > 10) {\
      warte[0] = 0;\
      animationnr[0] = animationnr[0] + 1; \
      if (animationnr[0] > hex_ani[0].length-1) { animationnr[0] = 0;}\
    }\
}\
\
function render1 () {\
    var c = document.getElementById('spriteEndeCanvas');\
    var ctx = c.getContext('2d');\
    ctx.fillStyle = '#FF0000';\
    ctx.clearRect(0, 0, 200, 100);\
    x[1] = 10;\
    y[1] = 80;\
    var hex = hex_ani[1][animationnr[1]].match(/.{1,2}/g);\
    var bin;\
    for (h = 0; h < hex.length; h++) {\
       bin = hex2bin(hex[h]).split('');\
       for (i = 0; i < bin.length; i++) {\
        \
        if (bin[i]==1) {\
          ctx.fillRect(x[1],y[1],10,10);\
        } else {\
          ctx.fillRect(x[1],y[1],0,0);\
        }\
        y[1]-=10;\
      }\
      x[1]+=10;\
      y[1]=80;\
    }\
    ctx.stroke();\
    warte[1]++;\
    if (warte[1] > 10) {\
      warte[1] = 0;\
      animationnr[1] = animationnr[1] + 1; \
      if (animationnr[1] > hex_ani[1].length-1) { animationnr[1] = 0;}\
    }\
}\
\
\
function hex2bin(hex){\
    return (parseInt(hex, 16).toString(2)).padStart(8, '0');\
}\
\
</script>";

const char* intensityHTML = "<label for='intensity'>Helligkeit <span id='intensityValue'></span><label><br/>\
<input type='range' min='0' max='15' value='0' class='slider' id='intensity' name='intensity'>\
<script>\
var slider = document.getElementById('intensity');\
var output = document.getElementById('intensityValue');\
output.innerHTML = slider.value;\
slider.oninput = function() {\
    output.innerHTML = this.value;\
}\
</script>\
<br>";

