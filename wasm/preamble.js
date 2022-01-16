Module['print'] = function(message) {
  sosiconPrint(message);
}
Module['onAbort'] = function() {
  sosiconAbort();
  sosiconPrint('');
  sosiconPrint('Program unexpectedly terminated!', 'blink infinite red');
  sosiconPrint(' <i class="bomb icon"></i> Most of the time this comes from memory exhaustion.');
  sosiconPrint('If you are on a mobile device, try switching to a laptop');
  sosiconPrint('or desktop computer.');
  sosiconPrint('You can also try a smaller input file.');
}
