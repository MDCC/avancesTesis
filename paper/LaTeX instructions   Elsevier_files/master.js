/*
 *  master.js | Main Javascript File
 *  @Author: [GW] - Gwidon Walinski (Squiz)
 *  @Author: [AC] - Artur Ciesciow [Squiz]
 *  @Author: [MCz] - Michal Czebotar [Squiz]
 *  @Author: [WS] - Wocjiech Szymanski [Squiz]
 *  @Author: [GT] - Gareth Trufitt [Squiz]
 *
 *  Table of content:
 *  1. Document ready
 *    1.0 Add 'js' class to body to detect that javascript is enabled [GW]
 *    1.1 Slider [GW]
 *    1.2 Open in new tab [GW]
 *    1.3 Set width for media boxes [GW]
 *    1.4 Aside menu adjustments [GW]
 *    1.5 Homepage news [GW]
 *    1.6 Product long description show and hide [GW]
 *    1.7 Close menu when clicked somewhere around - for toutch devices [GW]
 *    1.8 Main navigation - Add class to change rounded corner to square one when submenu is visible [GW]
 *    1.9 Advance search - search on Sci Verse [GW]
 *    1.10 Expander functionality for aims&scope on journals and description on books and book series [AC]
 *    1.11 Expand List function starter for subjects landing pages [AC]
 *    1.12 Show specific amount of elements in a pod box [AC]
 *    1.13 Display hover popups on Journal Impact Box [AC]
 *    1.14 Script to show Advanced search dropdown if advanced=true
 *    1.15 Advanced search box show/hide link on results page.
 *    1.16 Redirect to 404 Results if ErrorMsg returns from Funnelback
 *    1.17 Adds class to every third row of Most Cited elements
 *    1.18 Expander for product pods
 *    1.19 Fire LHS BG position fix
 *    1.20 Encode email sent via post for Editorial Board Contact Form
 *    1.21 Add class 'external' to external links
 *    1.22 Fires function for Browse more-less expand [func 2.9]
 *    1.23 Active state for products on browse pages
 *    1.24 Boxed Layouts Images slider
 *    1.25 Handle AJAX requests for the Editorial Board Contact Form
 *    1.26 Fix for Top Share icons position
 *    1.27 Highlight current subject in BigFooter, equalize BigFooter columns [MC]
 *    1.28 Highlight current page in Inner Top Level Nav [MC]
 *    1.29 Apply content opening in lightbox for any link with a specific class [WS]
 *    1.30 Add first and last classes to inline-list [GT]
 *
 *  2. Functions & jQuery Plugins
 *    2.1  Expand list function for subject landing pages [AC]
 *    2.2  Show specific amount of elements in a box - Journals Pods related script [AC]
 *    2.3  Extension to read GET variable value
 *    2.4  Function to open element in new card - used to bind event to element loaded with js
 *    2.5  Expander functions to avoid issue with <a> tag breaking expand functionality
 *    2.6  Set proper height on subject page
 *    2.7  Expander function for Product pods
 *    2.8  Fix for BG position of LHS column separator if column is not wide enough
 *    2.9  Browse more-less expand function
 *    2.91 Populate value or text of input or span with data from target asset
 *  3. Objects
 *
 */


/*
 *  1. DOCUMENT READY
 */
jQuery(document).ready(function($){

    // Add 'js' class to body to detect that javascript is enabled
    $('body').addClass('js');

    // 1.1 Slider [GW]
    // Build slider mark-up (GT 25/11/13)

    $('.js-slider_tri-content').addClass('slides');

    var listItems = $('.js-slider_tri-content .l-tri-content--item');
    for( var i = 0; i < listItems.length; i+=3 ) {
        listItems.slice(i, i+3)
            .wrapAll('<li><div class="slide-content-wrap"><ul class="l-tri-content no-bullets"></ul></div></li>');
    }

    // Initialize slider
    // Changed to .js-slider instead of #homepage-slider by GT 11/11/13
    $('.js-slider').each(function (){
        var $this = $(this),
        // Check if we should add arrows
            withArrows = ($this.hasClass('js-slider_arrows'))?true:false,
        // Check if we should show the nav dots
            withBottomNav = ($this.hasClass('js-slider_no-nav'))?false:true,
        // Check if we want the slider to loop
            loopSlider = ($this.hasClass('js-slider_loop'))?true:false,
        // Check if we want the slider to be automatic
            autoSlider = ($this.hasClass('js-slider_auto'))?true:false;

        $this.flexslider({
            animation: 'slide',
            slideshowSpeed: 9000,
            directionNav: withArrows,
            controlNav: withBottomNav,
            multipleKeyboard: true,
            animationLoop: loopSlider,
            slideshow: autoSlider
        });

        $('.flex-prev, .flex-next').addClass('ir');
    });

    // Add spans to slide controls (small dots) - that fix issues in IE6 and IE7
    $('.js-slider .flex-control-nav li a').each(function(){
        $(this).html( '<span>'+ $(this).text() +'</span>' );
    });

    // 1.2 Open in new tab [GW]
    /* Conflict with 2.4 - removed by nnogueira@squiz.co.uk 2012.10.24
     $('a.external, a.new-tab, a[rel="external"]').each(function(){
     $(this).attr('target', '_blank' );
     });
     */

    // 1.3 Set width for media boxes [GW]
    // When image is loaded
    $('.media.picture img, .media.movie iframe').load(function(){
        $(this).parent('div.media').css('width', $(this).width());
    });

    // When document is ready
    $('.media.movie iframe, .media.picture img').each(function(){
        $(this).parent('div.media').css('width', $(this).width());
    });

    // 1.4 Aside menu adjustments [GW]
    // Add class when aside item has submenu
    $('#aside > ul > li > ul').parent().addClass('with-submenu');

    // Set equal height with content box
    var contentBoxHeight = $('#content').height();
    var asideBoxHeight = $('#aside').height();
    var columnsLayoutHeight = $('#columns-layout .main').height();

    if ( asideBoxHeight < contentBoxHeight ){
        $('#aside').css('height', contentBoxHeight);
    }
    if ( asideBoxHeight < columnsLayoutHeight ){
        $('#aside').css('height', columnsLayoutHeight);
    }

    // 1.5 Homepage news [GW] - Disabled on Client Request
    /*  $('#homepage-news .other ul li a').click(function(e){
     e.preventDefault();

     var newsBoxObj = $('#homepage-news .news');
     var newsBoxHeight = newsBoxObj.css('height');
     var ajaxRequestURL = $(this).attr('href') + '?SQ_DESIGN_NAME=blank&t=' + new Date().getTime();
     // Loading screen
     newsBoxObj.html('').addClass('loading').css('height', newsBoxHeight);

     // Perform AJAX request to get new content
     $.get( ajaxRequestURL, function(data, textStatus){
     var dataObj = $(data).children('li:lt(3)').appendTo(newsBoxObj).removeAttr('style');
     newsBoxObj.removeClass('loading').children('li').fadeIn('fast');
     });
     });
     */
    // 1.6 Product long description show and hide [GW]
    /*var productDescriptionObj = $('.product-card .description');
     $('.dropdown', productDescriptionObj).click(function(e){
     e.preventDefault();
     $('.description-short', productDescriptionObj).toggle();
     $('.description-long', productDescriptionObj).toggle();
     });
     */
    // 1.7 Close menu when clicked somewhere around - for toutch devices [GW]
    /* removed by nnogueira@squiz.co.uk 2012.10.26 - causing issues on iPhone
     $('body:not(.menu)').live('touchstart', function(){
     if ( $('.menu > li .submenu-wrapper:visible').length ){
     $('.menu > li').trigger('mouseout');
     }
     });
     */

    // 1.8 Main navigation - Add class to change rounded corner to square one when submenu is visible [GW]
    var menuClass = '';
    $('.menu > li').hover(
        function(){
            menuClass = 'submenu-visible-' + $(this).attr('class');
            $(this).parent().addClass(menuClass);
        },
        function(){
            menuClass = 'submenu-visible-' + $(this).attr('class');
            $(this).parent().removeClass(menuClass);
        }
    );

    // 1.9 Advance search - search on Sci Verse [GW]
    $('.advance-search .sci-verse input.submit').click(function(){
        var searchQuery = encodeURIComponent( $(this).prev('input.text').val() );
        var searchURL = 'http://search1.sciencedirect.com?query=' + searchQuery;
        window.open(searchURL,'_blank');
    });

    // 1.10 Expander functionality for aims&scope on journals and description on books and book series [AC]
    // requires jquery.expander plugin
    var expJournalObj = $('.product-card-journal').find('.description > .aims_and_scope');
    if(expJournalObj.length > 0){
        simpleExpander(expJournalObj, 'full aims and scope');
    }

    var expBookObj = $('.product-card').find('.description > .book-description');
    if(expBookObj.length > 0){
        simpleExpander(expBookObj, 'full description');
    }

    // 1.11 Expand List function starter for subjects landing pages [AC]
    expandList('a.expand','li','ul.subcategory-list');


    // 1.12 Show specific amount of elements in a pod box [AC]
    /* recent articles */
    showXItemsOnly('.recent_articles','9', 'li:last > .see_more_links');

    /* most cited pod box */
    showXItemsOnly('.most_cited','9', 'li:last > .see_more_links');
    showXItemsOnly('.most_downloaded','9', 'li:last > .see_more_links');
    showXItemsOnly('.recent_articles','9', 'li:last > .see_more_links');

    // 1.13 Display hover popups on Journal Impact Box [AC]
    var popupName = '';
    $('.details-box').find('p.popup').hover(
        function(){
            popupName = $(this).data('popupname');
            $('.details-box').find('span[rel="'+popupName+'"]').removeClass('hide');
        },
        function(){
            $('.details-box').find('span[rel="'+popupName+'"]').addClass('hide');
        }
    );

    //1.14 Script to show Advanced search dropdown if advanced=true
    var advancedSearch = $.getUrlVars()["advanced"];
    if(advancedSearch === "true"){
        jQuery('.advance-form').css('display','block');
        subjectAsideHeight();
    }


    // 1.15 Advanced search box show/hide link on results page.
    if(jQuery('#advance-your-search-button a')){
        if (jQuery('.advance-form').css('display') === "none"){
            jQuery('#advance-your-search-button a').toggle(
                function(){ $(this).parent('div').siblings('.advance-form').show(); subjectAsideHeight();},
                function(){ $(this).parent('div').siblings('.advance-form').hide(); subjectAsideHeight();}
            );
        }
        else{
            jQuery('#advance-your-search-button a').toggle(
                function(){ $(this).parent('div').siblings('.advance-form').hide();},
                function(){ $(this).parent('div').siblings('.advance-form').show();}
            );
        }
    }


    // 1.16 Redirect to 404 Results if ErrorMsg returns from Funnelback
    if (($('#errorflag')) && ($('#errorflag').attr('value') === 'true')){
        /* var url = window.location.pathname;
         window.location.href = "/404"+url; */
        window.location.href = "/301";
    }
    // 1.17 Adds class to every third row of Most Cited elements
    $('.most_cited tr:nth-child(3n)').addClass('row-space');
    $('.most-cited-sub tr:nth-child(3n)').addClass('row-space');
    $('.most_downloaded tr:nth-child(3n)').addClass('row-space');
    $('.most-downloaded-sub tr:nth-child(3n)').addClass('row-space');
    $('.recent_articles tr:nth-child(3n)').addClass('row-space');
    $('.recent-articles-sub tr:nth-child(3n)').addClass('row-space');

    // 1.18 Expander for product pods
    if ($('.long-pod-description').length > 0){ podExpander($('.long-pod-description'), 930);}

    // 1.19 Fire LHS BG position fix
    fixAsideSeparatorPosition();

    // 1.20 Encode email sent via post for Editorial Board Contact Form
    /* Encodes email to send it properly to Matrix via post as system stripes @ from email address */
    $('.form-editorial-board #yourEmail').blur(function(){
        $('.form-editorial-board #encodedEmail').attr('value', $(this).attr('value').replace(/@/ig,'-AT-'));
    });

    // 1.21 Add class 'external' to external links [added by nnogueira@squiz.co.uk 2012.10.10] [edited by nnogueira@squiz.co.uk 2012.11.16 - filter out images]
    jQuery('#content').find('a').each(function(){
        if(jQuery(this).find('img').length == 0){
            var cLoc = jQuery(this).attr('href');
            if(typeof cLoc != "undefined" && jQuery(this).filter('[href*="elsevier-upgrade.squiz.co.uk"], [href*="elsevier.com"], [href*="search.html"]').length==0 && jQuery(this).filter('[href^="/"]').length == 0 && jQuery(this).filter('[href^="#"]').length==0) jQuery(this).addClass("external");
        }
    });

    // 1.22 Fires function for Browse more-less expand [func 2.9]
    $('.products ul.moreless').each(function(){browseReadMore($(this));});

    // 1.23 Active state for products on browse pages
    if ($('#aside ul li a[href="/products"]').parent('li').hasClass('active')){
        var thisUrlPath = window.location.pathname;
        var ulClass = thisUrlPath.substring(1,6);
        if (ulClass === "books"){ulClass = "browsebooks";}
        $('#aside ul li a[href="/products"]').siblings('ul').addClass(ulClass);
    }

    // 1.24 Boxed Layouts Images slider
    $('.content-box.slider').flexslider({
        animation: 'slide',
        slideshowSpeed: 15000,
        animationSpeed: 1000,
        directionNav: false,
        useCSS: false
    });

    // Add spans to slide controls (small dots) - that fix issues in IE6 and IE7
    $('.content-box.slider .flex-control-nav li a').each(function(){
        $(this).html( '<span>'+ $(this).text() +'</span>' );
    });

    // 1.25 Handle AJAX requests for the Editorial Board Contact Form
    if($('#memberFormData').length > 0){
        var url = $('#memberFormData').data('url').replace(/ /g,'%20');

        function setupMemberAjaxSubmit(){
            $('#memberFormData form').ajaxForm({
                target: '#memberFormData',
                type: 'POST',
                success: function(){
                    /*
                     * Run populate on input and span elements inside memberFormData that
                     * have a data-populate attribute.
                     */
                    populateData('memberFormData','memberFormData')
                    setupMemberAjaxSubmit();
                }
            });
        }

        $.ajax({
            url: url,
            type: 'GET',
            success: function(response){
                /*
                 * Modified by bagricola@squiz.co.uk 12/07/13
                 * to get around globals_get keyword escaping
                 * post-upgrade.
                 */
                $('#memberFormData').html(response);

                /*
                 * Run populate on input and span elements inside memberFormData that
                 * have a data-populate attribute.
                 */
                populateData('memberFormData','memberFormData')

                $('#memberFormData').show();

                setupMemberAjaxSubmit();
            }
        });
    }


    // 1.26 Fix for Top Share icons
    if(jQuery('.breadcrumb-wrapper.content-breadcrumb .breadcrumb').length === 0){
        jQuery('.breadcrumb-wrapper.content-breadcrumb').addClass('right');
        jQuery('#content').addClass('rel');
        jQuery('#content h1').addClass('short');
    }

    // 1.27 Highlight current subject in BigFooter, equalize BigFooter columns
    var currentSubject;
    currentSubject = jQuery('#aside h2').text();
    jQuery('#bigfooter-subjects-listing a').each(function() {
        if (jQuery(this).text() == currentSubject) {
            jQuery(this).addClass('bigfooter-current-subject');
        };
    });
    // remove divider background from the last column
    jQuery('.bigfooter-subjects-listing-col:last').addClass('last');
    // equalize BigFooter columns
    var maxHeight = 0;
    jQuery(".bigfooter-subjects-listing-col").each(function(){
        if ($(this).height() > maxHeight) { maxHeight = $(this).height(); }
    });
    jQuery(".bigfooter-subjects-listing-col").height(maxHeight);

    // 1.28 Highlight current page in Inner Top Level Nav
    var currentNavPage;
    currentNavPage = jQuery('#inner-top-level-nav').attr('class');
    jQuery('#inner-top-level-nav .' + currentNavPage).addClass('selected');
    jQuery('#inner-top-level-nav .' + currentNavPage);

    // 1.29 Apply content opening in lightbox for any link with a specific class
    $("a.lightbox-content").each(function() {
        // Removes target attribute
        if ($(this).attr("target") == "_blank") {
            $(this).removeAttr("target");
        }
        // Applies lightbox on each click
        $(this).click(function(e) {
            e.preventDefault();
            e.stopImmediatePropagation(); // Need to prevent this bubbling up to the silly ga.js handler
            var url = $(this).attr("href");
            // Get data for width, height and scroll
            $.getJSON(url + "?SQ_PAINT_LAYOUT_NAME=content-lightbox&SQ_DESIGN_NAME=content-lightbox", function(data) {
                // Set CSS for width, height and scroll within lightbox
                $("div.lb-content,div.lb-inner").width(data.Width);
                $("div.lb-content,div.lb-inner").height(data.Height);
                if (data.Scrollable == "1") {
                    $("div.lb-inner").css("overflow", "scroll");
                } else {
                    $("div.lb-inner").css("overflow", "hidden");
                }
                // Show lightbox with content
                lbgo(url, function(){
                    // Extra processing to shrink the box if only 1 image is inside
                    var inner_contents = $("div.lb-inner").children();
                    if ($("div.lb-inner").children().length == 1 && inner_contents[0].nodeName == "IMG") {
                        var img_width = inner_contents[0].width,
                            img_height = inner_contents[0].height;
                        if (img_width > 0 && img_height > 0) {
                            $("div.lb-content,div.lb-inner").width(img_width);
                            $("div.lb-content,div.lb-inner").height(img_height);
                        }
                    }
                });
            });
        });
    });

    $('.dropdown-trigger[data-target]').click(function(e) {
        var target = $('.dropdown-content[data-content="' + $(this).attr('data-target') + '"]');
        if(target.is(':visible')) {
            target.fadeOut(300)
        } else {
            target.fadeIn(300)
        }
    });


    $('.dropdown-wrapper').on('clickoutside',function() {
        if($(this).find('.dropdown-content').is(':visible')) $(this).find('.dropdown-content').fadeOut();
    });

    // 1.30 Add first and last class to inline-list elements

    $('.inline-list')
        .find('li:first-child').addClass('first-child')
        .end()
        .find('li:last-child').addClass('last-child');

    // 1.31 Load tab content on the homepage

    if ($('.js-ajax-tab-container').length) {
        loadTabContent('./?a=165600');
    }

});


/*
 *  2. FUNCTIONS & JQUERY PLUGINS
 */
// 2.1  Expand list function for subject landing pages [AC]
function expandList(parentSelector,rootElement,childSelector){
    jQuery(childSelector).hide();
    subjectAsideHeight();
    jQuery(''+parentSelector).toggle(
        function(){ jQuery(this).closest(rootElement).find(childSelector).slideDown(function(){subjectAsideHeight();}); jQuery(this).addClass('sub-expanded');},
        function(){ jQuery(this).closest(rootElement).find(childSelector).slideUp(function(){subjectAsideHeight();}); jQuery(this).removeClass('sub-expanded');}
    );
}

// 2.2 Show specific amount of elements in a box - Journals Pods related script [AC]
function showXItemsOnly(elementSelector, x, showMoreSelector){
    x = x-1;
    jQuery(''+elementSelector).find('table').find('tr:gt('+x+')').hide();
    jQuery(''+elementSelector).find(''+showMoreSelector).click(function(event){
        event.preventDefault();
        jQuery(''+elementSelector).find('table').find('tr:gt('+x+')').slideDown();
    });
}

//2.3  Extension to read GET variable value
$.extend({
    getUrlVars: function(){
        var vars = [], hash;
        var hashes = window.location.href.slice(window.location.href.indexOf('?') + 1).split('&');
        for(var i = 0; i < hashes.length; i++){
            hash = hashes[i].split('=');
            vars.push(hash[0]);
            vars[hash[0]] = hash[1];
        }
        return vars;
    }
});
//2.4  Function to open element in new card - used to bind event to element loaded with js

function openInNewCard(){
    //$('a.external, a.new-tab, a[rel="external"]').each(function(){
    $('a.new-tab, a[rel="external"]').each(function(){
        $(this).attr('target', '_blank' );
    });
}
// 2.5 Expander functions to avoid issue with <a> tag breaking expand functionality
function simpleExpander(expObj, expText){
    var slice = 150;
    var expHtml = expObj.html();
    var linkPos = expHtml.indexOf("<a");
    if ((linkPos !== -1) && (linkPos < slice)){ slice = linkPos-1; }
    expObj.expander({
        slicePoint: slice,
        expandText: '<br />View '+expText,
        userCollapseText: 'Hide '+expText,
        expandEffect: 'show',
        expandSpeed: 0,
        collapseEffect: 'hide',
        collapseSpeed: 0,
        afterExpand : function(){openInNewCard();}
    });
}
// 2.6 Set proper height on subject page
function subjectAsideHeight(){
    $('#aside').height('auto');
    $('#columns-layout .main').height('auto');
    var contentBoxHeight = $('#content').height();
    var asideBoxHeight = $('#aside').height();
    var columnsLayoutHeight = $('#columns-layout .main').height();

    if ( asideBoxHeight < contentBoxHeight ){
        $('#aside').css('height', contentBoxHeight);
    }
    if ( asideBoxHeight < columnsLayoutHeight ){
        $('#aside').css('height', columnsLayoutHeight);
    }
    fixAsideSeparatorPosition();
}

// 2.7 Expander function for Product pods
function podExpander(expObj, slice, expText, hideText){
    if (slice === undefined){slice = 250;}
    if (expText === undefined){expText = "<br /><span class='read-more'>Read more</span>";}
    if (hideText === undefined){hideText = "<br /><span class='read-more'>[ ^ ]</span>";}
    var expHtml = expObj.html();
    var linkPos = expHtml.indexOf("<a");
    expObj.expander({
        slicePoint: slice,
        expandText: expText,
        userCollapseText: hideText,
        expandEffect: 'show',
        expandSpeed: 0,
        collapseEffect: 'hide',
        collapseSpeed: 0,
        afterExpand : function(){openInNewCard();}
    });
}

// 2.8 Fix for BG position of LHS column separator if column is not wide enough
function fixAsideSeparatorPosition(){
/** change reverted by client request (nnogueira@squiz.co.uk) **
    var fillTop = 850;
    //var asideBgHeight = 1079; Reduced to fix #100921
    var asideBgHeight = 870;
    var asideHeight = $('#aside').height();
    if (parseInt(asideHeight) > asideBgHeight){
        $('#aside .aside-fill').remove();
        var fillHeight = parseInt(asideHeight) - fillTop;
        var fillHtml = "<div class='aside-fill' style='height: "+fillHeight+"px;'></div>";
        $('#aside .aside-footer').before(fillHtml);
    }
**/
}


// 2.9 Browse more-less expand function
function browseReadMore(readmoreObj, readmoreText){
    if (readmoreText === undefined){readmoreText = "View more";}
    if (readmoreObj.find("li:last").index() > 7){
        readmoreObj.find("li:gt(6)").hide();
        readmoreObj.find("li:last").after("<li class='readmore title'><a href='#'>"+readmoreText+"</a></li>");
        readmoreObj.find("li.readmore a").click(function(clickEvent){
            clickEvent.preventDefault();
            readmoreObj.find("li").show();
            readmoreObj.find("li.readmore").hide();
        });
    }
}

// 2.91 Populate value or text of input or span with data from target asset
function populateData(sourceId,destinationTree){
    $('#' + destinationTree + ' input[data-populate], #' + destinationTree + ' span[data-populate]').each(function() {
        if($(this).prop('tagName') == 'SPAN') {
            $(this).text($('#' + sourceId).data($(this).data('populate')));
        } else {
            $(this).val($('#' + sourceId).data($(this).data('populate')));
        }
    });
}

// 2.92 Load tab content via ajax

function loadTabContent (contentUrl) {
    $.ajax({
        url: contentUrl + '&SQ_DESIGN_NAME=blank',
        dataType: 'html',
        success: function (data) {
            var tabContents = $(data);
            tabContents.each(function (){
               var $this = $(this),
                   tabId = $this.data('tabid');

                if (tabId) {
                    $('#js-ajax-tab_' + tabId).html($this);
                }

                rerunJs($this);
            });
        },
        error: function () {

        }
    });
}

function rerunJs(context) {

    // Use the correct class for tabs with slider
    if ($('.slider', context).length) {
        var tab = context.parents('.tab'),
            $slider = context.find('.js-slider')
            // Check if we should add arrows
            withArrows = ($slider.hasClass('js-slider_arrows'))?true:false,
            // Check if we should show the nav dots
            withBottomNav = ($slider.hasClass('js-slider_no-nav'))?false:true,
            // Check if we want the slider to loop
            loopSlider = ($slider.hasClass('js-slider_loop'))?true:false,
            // Check if we want the slider to be automatic
            autoSlider = ($slider.hasClass('js-slider_auto'))?true:false;;

        // Ensure we are using the correct hidden classes
        if (tab.hasClass('hidden')) {
            tab.not('.active-tab').addClass('visually-hidden');
            tab.addClass('box-content_no-side-padding');
            tab.removeClass('hidden');
        }

        // Load slider
        $slider.flexslider({
            animation: 'slide',
            slideshowSpeed: 12000,
            directionNav: withArrows,
            controlNav: withBottomNav,
            multipleKeyboard: true,
            animationLoop: loopSlider,
            slideshow: autoSlider
        });

        $('.flex-prev, .flex-next').addClass('ir');

    }
}


/* new   */

// popup layer with helpbox iframe

function helpbox(url) {

    if((navigator.userAgent.match(/iPhone/i)) || (navigator.userAgent.match(/iPad/i)) || (navigator.userAgent.match(/Android/i))) {
        window.open(url);
    } else {

        resetPopups();

        var popup = jQuery(document.createElement('div'));
        var button_close = jQuery(document.createElement('div'));

        button_close.addClass('btn_close');
        button_close.attr('id', 'close-help');


        if (document.body.clientHeight < 500) {
            iframelink = '<iframe frameborder="0" style="width: 760px; height: 345px;" src="'+url+'"></iframe>';
            popup.addClass('helpbox_medium');
            button_close.addClass('btn_close');
            button_close.attr('id', 'close-help');

        } else {
            iframelink = '<iframe frameborder="0" style="width: 760px; height: 445px;" src="'+url+'"></iframe>';
            popup.addClass('helpbox');

        }

        popup.addClass('helpbox');


        var button_close = jQuery(document.createElement('div'));
        button_close.addClass('btn_close');
        button_close.attr('id', 'close-help');

        var helpbox = jQuery(document.createElement('div'));
        helpbox.addClass('viewerHelpbox');

        helpbox.append(iframelink);

        popup.append(button_close);
        popup.append(helpbox);

        jQuery('body').append(popup);
        popup.draggable();


        jQuery('#close-help').live('click', function() {
            jQuery('.helpbox').remove();
        });

    }
}


//Reset all popup layers

function resetPopups() {
    if(jQuery('.lightbox').length) {
        jQuery('.lightbox').hide();
    }
    if(jQuery('.editboard_box').length) {
        jQuery('.editboard_box').hide();
    }
    if(jQuery('.succes_box').length) {
        jQuery('.succes_box').hide();
    }
    if(jQuery('.overlay_whislist').length) {
        jQuery('.overlay_whislist').hide();
    }
    if(jQuery('.helpbox').length) {
        jQuery('.helpbox').hide();
    }
}

//  jQuery auto-hide placeholder text upon focus - date added 30 jan 2013 by dennis smit

$(function()
{
    $('input').focusin(function()
    {
        input = $(this);
        input.data('place-holder-text', input.attr('placeholder'));
        input.attr('placeholder', '');
    });

    $('input').focusout(function()
    {
        input = $(this);
        input.attr('placeholder', input.data('place-holder-text'));
    });
});

//  Prevent submitting empty queries with Global Search - date added 26 jun 2013 by dennis smit

$(document).ready(function() {
    $(".header .search form").submit(function() {
        if ($("input[type=text]").val() === "") {
            return false;
        }
        return true;
    });
});

// Added by Dennis Smit - 18 Oct 2013

$(document).ready(function () {
    function addMega() {
        $(this).addClass("hovering");
    }
    function removeMega() {
        $(this).removeClass("hovering");
    }
    var megaConfig = {
        interval: 200,
        sensitivity: 4,
        over: addMega,
        timeout: 250,
        out: removeMega
    };
    $(".header .menu li.dropdownDelay").hoverIntent(megaConfig);
});


/*
 *  3. OBJECTS
 */