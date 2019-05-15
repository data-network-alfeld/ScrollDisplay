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
</select><br></span>";

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
</select><br></span>";

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

