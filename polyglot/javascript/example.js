setup: function() {
  title("Zajal - JavaScript")
},

draw: function() {
  alpha_blending(true)

  translate(width()/2, height()/2)
  var limit = 150;

  for (var i = limit; i >= 0; i--) {
    var even = i % 2 == 0;
    fill(even);
    color(255, (i*1.0) / limit * 128)

    circle(
      Math.cos(i + time() * i/50.0) * i * 2,
      Math.sin(i + time() * i/50.0) * i * 2,
      10 + i);
  }
},

update: function() {
  // print("Update")
}