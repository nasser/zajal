$(document).ready(function(){

	hljs.initHighlightingOnLoad();
	hljs.tabReplace = '  ';

	$('#btn-nav').click(function(e) {
		$('section.sidebar, .content').toggleClass('menu-expand');
		$('header').toggleClass('header-slide');
		e.preventDefault();
	});

	$('#contents ul').each(function() {
    if ($(this).children().size() === 0) {
      return $(this).remove();
    }
  });

  return $("#quick-search").quicksearch('.searchable');

});