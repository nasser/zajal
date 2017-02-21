var current;
var next;

function renderer(container, initial) {
  current = initial;
  next = initial;
  
  container.appendChild( current.render().domElement );
  
  current.camera.render().aspect = window.innerWidth / window.innerHeight;
  current.camera.render().updateProjectionMatrix();
  current.render().setSize( window.innerWidth, window.innerHeight );
  
  var _update = function(newState) {
    next = newState;
  }
  
  var _render = function() {
    requestAnimationFrame(_render);
    if(current === next) return;
    
    current.reconcile(next);
    current = next;
    current.render().render( current.scene.render(), current.camera.render() );
  }

  
  return {
    update: _update,
    render: _render
  }  
}