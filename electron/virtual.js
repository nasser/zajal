/* api
  render() -> real (cache result in target)
  reconcile(other) -> void (diff + apply, caches results in other)
*/

// var drawfn = domClock; // need to undo threejs hacks to make work
// var drawfn = thunkTest;
var drawfn = threeTest;

// three experiment
var current = drawfn(new Date());
document.body.appendChild(current.render().domElement);
current._cachedRenderer.setSize( window.innerWidth, window.innerHeight );

var oldDate = new Date();

function loop(d) {
  var next = drawfn(new Date());
  current.reconcile(next);
  current = next;
  
  // cheat
  current.camera._cache.position.set(10, 0, 10);
  current.camera._cache.lookAt( current.scene._cache.position )
  
  current._cachedRenderer.render( current.scene._cache, current.camera._cache );
  
  requestAnimationFrame(loop)
}

loop(0);