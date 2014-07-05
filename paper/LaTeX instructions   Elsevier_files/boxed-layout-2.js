$(function () {

    /* ------------------------------------------ */
    /* ------------ Fix page height ------------- */
    /* commented by lwoollett@squiz.co.uk (Hugh)
    function fixPageHeight() {
        $('#aside .aside-fill').remove();
        $('#aside').css('height', 'auto');
        var fillTop = 850;
        //var asideBgHeight = 1079; Fixing issue #100921
        var asideBgHeight = 875;
        var asideHeight = $('#content').height();
        asideHeight = parseInt(asideHeight, 10);
        if (asideHeight > asideBgHeight) {
            $('#aside .aside-fill').remove();
            var fillHeight = asideHeight - fillTop;
            var fillHtml = "<div class='aside-fill' style='height: " + fillHeight + "px;'></div>";
            $('#aside .aside-footer').before("<div class='cleat'></div>");
            $('#aside .aside-footer').before(fillHtml);
            $('#aside').height(asideHeight);
        } else {
            $('#aside').height(asideBgHeight);
        }
    }
    */
    // fire only when Boxed Layout
    if ($('.boxed').length > 0) {


        // 1.25 Boxed Layout: Full width content slider
        $('.content-box.content-slider .box-content').flexslider({
            animation: 'slide',
            slideshowSpeed: 15000,
            animationSpeed: 1000,
            directionNav: false,
            start: function () {
                //fixPageHeight();
              subjectAsideHeight(); //mcz
            }
        });


        // Add spans to slide controls (small dots) - that fix issues in IE6 and IE7
        $('.content-box.content-slider .flex-control-nav li a').each(function () {
            $(this).html('<span>' + $(this).text() + '</span>');
        });

        // Fix for IE7, to disable redirect when href is not defined
        $('.content-box.content-slider .flex-control-nav li a').each(function () {

            $(this).attr('href', 'javascript:;');
        });

        // If slider with buttons is inside tabs, add class to remove padding
        function checkIfSlider () {
            $('.box-content').each(function(){
                var $this = $(this),
                    $slider = $this.find('.slider_side-arrows');

                if ($slider.length) {
                    $this.addClass('box-content_no-side-padding')
                }
            });
        }


        /* BL5: Align table cells when image is inside */
        $('.boxed table tr td').each(function () {
            if ($(this).find('img').length > 0) {
                $(this).addClass('center-align');
            }
        });


        /* Adds class to every third button - IE7 fix */
        $('.boxed').find('.box.button:nth-child(3n)').addClass('third');

        /* Aligns halfwidth boxes - IE fix*/
        $('.boxed').find('.halfwidth:odd').each(function () {
            if ($(this).prev("div").hasClass("halfwidth")) {
                $(this).addClass("end");
            }
        });

        /* Tweak: Reduce top padding for boxes with no header */
        jQuery('.content-box .box-header.noheader').next('.box-content').addClass('reduce-top');

        /* Adding clear div after each row end for halfwidth boxes */
        jQuery(".halfwidth.end").after("<div class='clear'></div>");

        /* Make sure that LHS Separator length is correct */
        setTimeout(function () {
            //fixPageHeight();
        }, 350);

    } // End if

    /* -- Elsevier Tabs function start -- */

    function _ElsevierTabs(options) {
        var t = this;
        var settings = {};

        function init(options) {

            // Default settings
            settings = $.extend({
                'selector': '.tabs-normal',
                'type': 'normal',
                'tabsSettings': {}
            }, options);

            // Create menu
            $(settings.selector).each(function () {
                createMenu($(this)); // Create menu
                $(this).tabs(settings.tabsSettings); // Initialize jQuery UI Tabs
                adjustPaddings($('.tabs-menu', $(this)));
            });

        }

        function createMenu(TabsWrapperObj) {
            var tabs = $('.tab', TabsWrapperObj);

            if (tabs.length) {
                var menuHTML = '<div class="box-header"><ul class="tabs-menu tabs-number-' + tabs.length + '">';
                for (i = tabs.length - 1; i >= 0; i--) {
                    var tabObj = $(tabs[i]);
                    var tabTitle = tabObj.data('title');
                    var itemClass = '';
                    var after = (settings['type'] == 'process') ? '<span></span>' : '';
                    var itemID = (tabObj.attr('id')) ? tabObj.attr('id') : tabTitle.replace(/\ /ig, '-');
                    itemID = tabObj.data("useid");
                    if (i == 0) {
                        itemClass = 'first';
                    } else if (i == tabs.length - 1) {
                        itemClass = 'last';
                        after = ''; // We do not need extra span in last item
                    }

                    tabObj.attr('id', itemID);
                    menuHTML += '<li class="' + itemClass + '"><a href="#' + itemID + '">' + unescape(tabTitle) + '</a>' + after + '</li>';
                }

                menuHTML += '</ul></div>';
                TabsWrapperObj.prepend(menuHTML);
            }
        }

        function adjustPaddings(menuObj) {
            $('a', menuObj).each(function () {
                var maxAvaiableHeight = $(this).parent().height() - 2; // -2 is for top and bottom border width
                var currentObjectHeight = $(this).height();

                // If link is bigger then avaiable space ...
                if (currentObjectHeight > maxAvaiableHeight) {
                    $(this).css('height', maxAvaiableHeight);
                    return false;
                }

                var paddingTop = Math.floor((maxAvaiableHeight - currentObjectHeight) / 2);
                var paddingBottom = maxAvaiableHeight - currentObjectHeight - paddingTop;

                // apply styles
                $(this).css({
                    'paddingTop': paddingTop,
                    'paddingBottom': paddingBottom
                });

            });

        }

        init(options);
    }
    /* -- Elsevier Tabs function End -- */

    /* Generate rounded boxes start */

    function generateRoundedBox() {
        var tabbedBoxContent = ".tabbed-content .box-content";
        $(tabbedBoxContent).each(function () {
            $(this).find("blockquote").each(function () {
                makeBoxes($(this));
            });
        });
    }

    function makeBoxes(elemObj) {
        var elemClass = elemObj.children().eq(0).attr('class');
        if (elemClass === undefined) {
            elemClass = "rounded-box";
        }

        var elemClassArray = elemClass.split(' ');
        elemClass = "";
        for (var i in elemClassArray) {
            if ((elemClassArray[i] === "rounded-box") || (elemClassArray[i] === "rounded-box-wide") || (elemClassArray[i] === "rb-left") || (elemClassArray[i] === "rb-right")) {
                elemClass += elemClassArray[i] + " ";
            }
        }
        if (elemClass.length < 2) {
            elemClass = "rounded-box";
        }
        var elemHtml = elemObj.html();
        elemObj.replaceWith("<div class='" + elemClass + "'>" + elemObj.html() + "</div>");
    }
    /* Generate rounded boxes end */



    /* Print proper structure for tabs */

    function printAndRemove(tabbedHtml, tabbedSelector) {
        tabbedSelector.last().after(tabbedHtml);
        tabbedSelector.each(function () {
            $this = $(this);
            if ($this.attr('id', 'tabbed')) {
                $this.prev('div.clear').remove();
                $this.next('div.clear').remove();
                $this.remove();
            }
        });
    }

    function cleanInput (input) {
        return input.replace(/[ ]/g, "-").replace(/[^A-Za-z0-9-_]/g, '').replace(/[-]*$/g, "").replace(/^[-]*/g, "").toLowerCase();
    }

    function generateTabbed() {
        /* If there are multiple tabs on a page, wrap each of them in a div with class of tab-container */
        var tabbedSelector = ".tabbed-content";
        var tabContainer = $('.tab-container');
        var headerSelector = ".box-header h2";
        var contentSelector = ".box-content";

        var tabHeader = "";
        var tabContent = "";
        var tabbedHtml = "";

        var useNoArrows = false;
        var tabType = ".tabs-process";

        var showHideFlag = "";

        if (tabContainer.length) {
            tabContainer.each(function (){
                buildTabs($(this).find(tabbedSelector));
            });
        } else {
            buildTabs($(tabbedSelector));
        }

        function buildTabs(tabbedSelector) {
            tabbedSelector.each(function (){
                if ($(this).data('tabbed').indexOf('show-box') !== -1) {
                    showHideFlag = "show-box ";
                }
                else if ($(this).data('tabbed').indexOf('hide-box') !== -1) {
                    showHideFlag = "hide-box ";
                }
            });

            var tabbedBoxId = "";
            tabbedHtml += "<div class='clear'></div><div id='tabbed' class='content-box "+showHideFlag+"tabbed-content tabs-process'>";
            tabbedSelector.each(function () {

                if ($(this).data('tab-headings') === 'full-html') {
                    tabHeader = $(this).find(headerSelector).html();
                } else {
                    tabHeader = $(this).find(headerSelector).text();
                }

                tabbedBoxId = cleanInput(tabHeader);
                if (tabbedBoxId === ""){
                   tabbedBoxId = $(this).attr("id");
                }

                tabContent = $(this).find(contentSelector).html();

                if ($(this).data('tabbed').indexOf('noarrows') !== -1) {
                    useNoArrows = true;
                }
                tabbedHtml += "<div class='tab box-content' data-title='" + escape(tabHeader) + "' data-useid='" + tabbedBoxId + "'>";
                tabbedHtml += "" + tabContent + "";
                tabbedHtml += "</div>";
            });
            tabbedHtml += "<div class='box-footer'></div></div><!-- closing tag form main box --><div class='clear'></div>";

            if (useNoArrows === true) {
                tabbedHtml = tabbedHtml.replace("tabs-process", "tabs-normal");
                tabType = ".tabs-normal";
            }

            printAndRemove(tabbedHtml, $(tabbedSelector));
            tabbedHtml = '';
        }


        /* do the tabs */
        // Create normal tabs
        _ElsevierTabs({
            'selector': '.tabs-normal',
            'type': 'normal'
        });

        // Create tabs with arrows
        _ElsevierTabs({
            'selector': '.tabs-process',
            'type': 'process'
        });

        var tabBoxContent = $('.tab.box-content');
        // If the tabs contain a slider, use visually hidden class so we maintain width
        tabBoxContent.each(function(){
            var $this = $(this);
            if ($this.find('.slider').length) {
                $this.addClass('visually-hidden');
            } else {
                $this.addClass('hidden');
            }
        });

        $('.tabs-menu a').each(function (k, v) {
            $(this).attr('id', '');
        });

        // Navigate to correct tab on loading
        if (!$('.tab-container').length) { // Only use hash when there is only one set of tabs on a page
            onHashChange(true);

            /* Bind hashchange event (using jquery.hashchange in thirdparty.js) */
            $(window).hashchange(onHashChange);
            //window.onhashchange = onHashChange;
        } else {
            checkTabCookie();
        }
    }

    /* --- Generate Tabbed Box Start --- */
    /* --- Generate Tabbed Box End --- */


    /* --- Tab Switching / URL Hash Start --- */
    function getHashFromHref(href) {
        // If href contains #, then return everything after the last #
        return (href.indexOf('#') !== -1)? href.split('#').pop() : false;
    }

    function getHrefWithoutHash(href) {
        // If href contains #, then return everything before the first #
        return (href.indexOf('#') !== -1)? href.substr(0, href.indexOf('#')) : href;
    }

    function sanitizeHash(hash) {
        return (hash.indexOf('#') === 0)? hash.substr(1) : hash;
    }

    function onHashChange(initial) {

        // If we support location.hash, use that, otherwise use Href to grab the hash.
        var newHash = (window.location.hash)? sanitizeHash(window.location.hash) :
            getHashFromHref(window.location.href);

        // Generate active tab selector: If initial load and no specified hash, use default (first tab)
        // Otherwise, select the tab with '#newHash' at the end of its' href.
        var new_active_tab_selector = (!initial || (newHash && newHash !== ''))?
            '#tabbed ul.tabs-menu a[href$="#' + newHash + '"]' :
            '#tabbed ul.tabs-menu li.first a';

        // Set the new active tab using the selector above
        var new_active_tab = $(new_active_tab_selector);

        // Check if a tab exists with this href
        if (new_active_tab.length === 1) {

            // Default newHash to the first tag if not set
            if(!newHash) {
                newHash = getHashFromHref(new_active_tab.attr('href'));
            }

            showTab(new_active_tab, newHash);

        }
    }

    /* Check tab cookie - If we are using cookies to store the tab location instead of hash (multiple tabs on page for example) */
    function checkTabCookie () {
        var $tabContainer = $('.tab-container');

        $tabContainer.each(function (i){
            var $this = $(this),
                $thisId = 'tabContainer' + i;

            if ($this.data('tabs-use-cookie') === 'yes') {

                var currentLoc = getHrefWithoutHash(location.href),
                    currentLocClean = cleanInput(currentLoc),
                    cookieVal = $.cookie(currentLocClean + $thisId),
                    new_active_tab = $this.find('#tabbed ul.tabs-menu li.first a'),
                    newHash = '';

                $this.data('tab-container-id', $thisId);

               if (cookieVal) {
                   new_active_tab_selector = '#tabbed ul.tabs-menu a[href$="#' + cookieVal + '"]';
                   $new_active_tab = $(new_active_tab_selector);
                   if ($new_active_tab.length) {
                       new_active_tab = $new_active_tab;
                   }
               }

                newHash = getHashFromHref(new_active_tab.attr('href'));
                showTab(new_active_tab, newHash, $this);
            }
        });

    }

    function setTabCookie (newHash, $container) {
        var currentLoc = getHrefWithoutHash(location.href),
            currentLocClean = cleanInput(currentLoc),
            cookieName = currentLocClean + $container.data('tab-container-id');

        if ($container.data('tabs-use-cookie') === 'yes') {
            $.cookie(cookieName, newHash);
        }
    }

    function tabEvents () {
        $('.tab-container').each(function (){ // Tab events only apply to pages with multiple tabs as they don't use hash

            var $thisContainer = $(this);
            $thisContainer.find('.tabs-menu a').click(function (e){

                var $this = $(this),
                    newHash = getHashFromHref($this.attr('href'));

                showTab($this, newHash, $thisContainer);
                setTabCookie(newHash, $thisContainer);
                e.preventDefault();
            });
        });
    }

    function showTab (new_active_tab, newHash, context) {
        var hiddenClass = 'hidden';
        if (!context) {
            context = $('.tabbed-content');
        }
        // If the tabs contain a slider, use visually hidden class so we maintain width
        if ($('.slider', context).length) {
            hiddenClass = 'visually-hidden';
        }
        // If so, remove any current active class
        $('.ui-tabs-active', context).removeClass('ui-tabs-active');

        // Activate the list item above the matching href
        new_active_tab.parent().addClass('ui-tabs-active');


        // Hide the current active tab
        $('.active-tab', context).removeClass('active-tab').addClass(hiddenClass);

        // Display the new active tab using its useid
        $('[data-useid="' + newHash + '"]').addClass('active-tab').removeClass(hiddenClass);
    }

    /* --- Tab Switching / URL Hash End --- */


    /* Generate Tabbed box */
    generateTabbed();

    // fire only when Boxed Layout
    if ($('.boxed').length > 0) {
        //fixPageHeight();
    }
    

    /* Register tabEvents */
    tabEvents();

    if ($('.boxed').length > 0) {
        /* Remove padding for tabs containg sliders */
        checkIfSlider();
    }

});


/* ------------------------------------------------ */
/* ----- Show/Hide Feature  ----- */
/* ------------------------------------------------ */

/* ---- Global helpers functions ---- */
var Elsevier = Elsevier || {};  // namespace definition
Elsevier.namespace = function (ns_string) {
    var parts = ns_string.split('.'), parent = Elsevier, i;
    //strip redundant leading global
    if (parts[0] === "Elsevier") { parts = parts.slice(1); }
    for (i = 0; i < parts.length; i += 1) {
        //create a property if it doesn't exist
        if (typeof parent[parts[i]] === "undefined") { parent[parts[i]] = {}; }
        parent = parent[parts[i]];
    }
    return parent;
};

/* ------------------------------------------ */

Elsevier.namespace('Elsevier.ShowHide');
Elsevier.ShowHide = {
    selectors:{
        freetext: "div.free-text",
        freetextHeader: "h2:eq(0)",
        freeTextContent: "*:not(h2:first):not(h2 >span)",
        podBox: "div.pod-box",
        podBoxHeader: "div.box-header",
        podBoxContent: "div.box-content",
        podBoxFooter: "div.box-footer",
        tabbedShow: "#tabbed.show-box",
        tabbedHide: "#tabbed.hide-box",
        tabbedHeader: "div.box-header",
        tabbedContent: "div.box-content",
        tabbedActive: "div.active-tab",
        tabbedFooter: "div.box-footer"
    },
    vars:{
        showFlag: "show",
        hideFlag: "hide",
        roundedHeaderClass: "rounded",
        plusPattern: "<span class='icon show'></span>",
        minusPattern: "<span class='icon hide'></span>",
        clearfix: "<div class='clear'></div>"
    },
    init: function(){
        // we are using data-shf parameter

        // podboxes hide
        jQuery(Elsevier.ShowHide.selectors.podBox+"[data-shf*='hide-box']").each(function(){
            Elsevier.ShowHide.podBoxHide(jQuery(this));
        });
        // podboxes show
        jQuery(Elsevier.ShowHide.selectors.podBox+"[data-shf*='show-box']").each(function(){
            Elsevier.ShowHide.podBoxShow(jQuery(this));
        });

        // freetext hide
        jQuery(Elsevier.ShowHide.selectors.freetext+".hide-box").each(function(){
            Elsevier.ShowHide.freeTextHide(jQuery(this));
        });

        // freetext show
        jQuery(Elsevier.ShowHide.selectors.freetext+".show-box").each(function(){
            Elsevier.ShowHide.freeTextShow(jQuery(this));
        });

        // tabbed hide
        jQuery(Elsevier.ShowHide.selectors.tabbedHide).each(function(){
            Elsevier.ShowHide.tabbedHide(jQuery(this));
        });

        // tabbed show
        jQuery(Elsevier.ShowHide.selectors.tabbedShow).each(function(){
            Elsevier.ShowHide.tabbedShow(jQuery(this));
        });

    },
    podBoxHide: function(thisObj){
        // add clickable span to the page
        // means box is hidden by default
        thisObj.find(Elsevier.ShowHide.selectors.podBoxHeader).append(Elsevier.ShowHide.vars.plusPattern+Elsevier.ShowHide.vars.clearfix);
        thisObj.find(Elsevier.ShowHide.selectors.podBoxHeader).find("h2").addClass("show-hide");
        thisObj.find(Elsevier.ShowHide.selectors.podBoxContent).hide();
        thisObj.find(Elsevier.ShowHide.selectors.podBoxFooter).hide();
        thisObj.find(Elsevier.ShowHide.selectors.podBoxHeader).addClass(Elsevier.ShowHide.vars.roundedHeaderClass);
        thisObj.find(Elsevier.ShowHide.selectors.podBoxHeader+" span.icon").data("status","collapsed");

        // click
        thisObj.find(Elsevier.ShowHide.selectors.podBoxHeader+" span.icon").click(function(){
            if (jQuery(this).hasClass("show")){ // pls expand
                jQuery(this).removeClass("show").addClass("hide");
                thisObj.find(Elsevier.ShowHide.selectors.podBoxHeader).removeClass(Elsevier.ShowHide.vars.roundedHeaderClass);
                thisObj.find(Elsevier.ShowHide.selectors.podBoxContent).slideDown("slow");
                thisObj.find(Elsevier.ShowHide.selectors.podBoxFooter).show();
            }
            else{ // collapse
                jQuery(this).removeClass("hide").addClass("show");
                thisObj.find(Elsevier.ShowHide.selectors.podBoxHeader).addClass(Elsevier.ShowHide.vars.roundedHeaderClass);
                thisObj.find(Elsevier.ShowHide.selectors.podBoxContent).slideUp("slow");
                thisObj.find(Elsevier.ShowHide.selectors.podBoxFooter).hide();
            }
        });
    },
    podBoxShow: function(thisObj){
        // add clickable span to the page
        thisObj.find(Elsevier.ShowHide.selectors.podBoxHeader).append(Elsevier.ShowHide.vars.minusPattern+Elsevier.ShowHide.vars.clearfix);
        thisObj.find(Elsevier.ShowHide.selectors.podBoxHeader).find("h2").addClass("show-hide");
        thisObj.find(Elsevier.ShowHide.selectors.podBoxHeader+" span.icon").data("status","expanded");

        // click
        thisObj.find(Elsevier.ShowHide.selectors.podBoxHeader+" span.icon").click(function(){
            if (jQuery(this).hasClass("show")){ // pls expand
                jQuery(this).removeClass("show").addClass("hide");
                thisObj.find(Elsevier.ShowHide.selectors.podBoxHeader).removeClass(Elsevier.ShowHide.vars.roundedHeaderClass);
                thisObj.find(Elsevier.ShowHide.selectors.podBoxContent).slideDown("slow");
                thisObj.find(Elsevier.ShowHide.selectors.podBoxFooter).show();
            }
            else{ // collapse
                jQuery(this).removeClass("hide").addClass("show");
                thisObj.find(Elsevier.ShowHide.selectors.podBoxHeader).addClass(Elsevier.ShowHide.vars.roundedHeaderClass);
                thisObj.find(Elsevier.ShowHide.selectors.podBoxContent).slideUp("slow");
                thisObj.find(Elsevier.ShowHide.selectors.podBoxFooter).hide();
            }
        });
    },
    freeTextHide: function(thisObj){
        // add clickable span to the page
        // means text is hidden by default
        thisObj.find(Elsevier.ShowHide.selectors.freetextHeader).html("<span class='text'>" + thisObj.find(Elsevier.ShowHide.selectors.freetextHeader).text() + "</span>" + Elsevier.ShowHide.vars.plusPattern);
        thisObj.find(Elsevier.ShowHide.selectors.freetextHeader).after(Elsevier.ShowHide.vars.clearfix);

        thisObj.find(Elsevier.ShowHide.selectors.freeTextContent).hide();

        // click
        thisObj.find(Elsevier.ShowHide.selectors.freetextHeader+" span.icon").click(function(){
            if (jQuery(this).hasClass("show")){ // pls expand
                thisObj.find(Elsevier.ShowHide.selectors.freeTextContent).slideDown("slow");
                jQuery(this).removeClass("show").addClass("hide");
            }
            else{ // collapse
                jQuery(this).removeClass("hide").addClass("show");
                thisObj.find(Elsevier.ShowHide.selectors.freeTextContent).slideUp("slow");
            }
        });
    },
    freeTextShow: function(thisObj){
        // add clickable span to the page
        thisObj.find(Elsevier.ShowHide.selectors.freetextHeader).html("<span class='text'>" + thisObj.find(Elsevier.ShowHide.selectors.freetextHeader).text() + "</span>" + Elsevier.ShowHide.vars.minusPattern);
        thisObj.find(Elsevier.ShowHide.selectors.freetextHeader).after(Elsevier.ShowHide.vars.clearfix);

        // click
        thisObj.find(Elsevier.ShowHide.selectors.freetextHeader+" span.icon").click(function(){
            if (jQuery(this).hasClass("show")){ // pls expand
                thisObj.find(Elsevier.ShowHide.selectors.freeTextContent).slideDown("slow");
                jQuery(this).removeClass("show").addClass("hide");
            }
            else{ // collapse
                jQuery(this).removeClass("hide").addClass("show");
                thisObj.find(Elsevier.ShowHide.selectors.freeTextContent).slideUp("slow");
            }
        });
    },
    tabbedHide: function(thisObj){
        thisObj.find(Elsevier.ShowHide.selectors.tabbedHeader).append(Elsevier.ShowHide.vars.plusPattern);
        thisObj.find(Elsevier.ShowHide.selectors.tabbedContent).hide();
        thisObj.find(Elsevier.ShowHide.selectors.tabbedHeader).addClass(Elsevier.ShowHide.vars.roundedHeaderClass);
        thisObj.find(Elsevier.ShowHide.selectors.tabbedFooter).hide();

        thisObj.find(Elsevier.ShowHide.selectors.tabbedHeader+" span.icon").click(function(){
            if (jQuery(this).hasClass("show")){ // pls expand
                jQuery(this).removeClass("show").addClass("hide");
                thisObj.find(Elsevier.ShowHide.selectors.tabbedActive).slideDown("slow", function(){
                    thisObj.find(Elsevier.ShowHide.selectors.tabbedHeader).removeClass(Elsevier.ShowHide.vars.roundedHeaderClass);
                });
                thisObj.find(Elsevier.ShowHide.selectors.tabbedFooter).show();
            }
            else{ // collapse
                jQuery(this).removeClass("hide").addClass("show");
                thisObj.find(Elsevier.ShowHide.selectors.tabbedContent).slideUp("slow", function(){
                    thisObj.find(Elsevier.ShowHide.selectors.tabbedHeader).addClass(Elsevier.ShowHide.vars.roundedHeaderClass);
                });
                thisObj.find(Elsevier.ShowHide.selectors.tabbedFooter).hide();
            }
        });
    },
    tabbedShow: function(thisObj){
        thisObj.find(Elsevier.ShowHide.selectors.tabbedHeader).append(Elsevier.ShowHide.vars.minusPattern);
        thisObj.find(Elsevier.ShowHide.selectors.tabbedHeader+" span.icon").click(function(){
            if (jQuery(this).hasClass("show")){ // pls expand
                jQuery(this).removeClass("show").addClass("hide");
                thisObj.find(Elsevier.ShowHide.selectors.tabbedActive).slideDown("slow", function(){
                    thisObj.find(Elsevier.ShowHide.selectors.tabbedHeader).removeClass(Elsevier.ShowHide.vars.roundedHeaderClass);
                });
                thisObj.find(Elsevier.ShowHide.selectors.tabbedFooter).show();
            }
            else{ // collapse
                jQuery(this).removeClass("hide").addClass("show");
                thisObj.find(Elsevier.ShowHide.selectors.tabbedContent).slideUp("slow", function(){
                    thisObj.find(Elsevier.ShowHide.selectors.tabbedHeader).addClass(Elsevier.ShowHide.vars.roundedHeaderClass);
                });
                thisObj.find(Elsevier.ShowHide.selectors.tabbedFooter).hide();
            }
        });
    }
};

/* ------------------------------------------------ */
/* ----- Show/Hide Feature End ----- */
/* ------------------------------------------------ */

/* Open Access Table CR Start */
/**
 @name: Open Access Table CR
 @author: Artur Ciesciow [Squiz]
 @description: Dynamically populates table with amount of Journals taken from FB source. Link to FB is defined in OpenAccessTable obj in vars section.
 This functionality uses Boxed Layout. Values are populated in items with classes: .open-access-normal and .open-access-support
 Also functionality displays popups for elements that uses .oa-popup classes; popup content...

**/
var OpenAccessTable = {
   vars:{ // stores all variables
      optionalValue: "1645", // TEMP - because we don't have dynamic data source yet
      fbResourceUrl: "/administration/oadd/oa-journals", // assetId = #167440
      highlightClass: "highlight",
      t: null,
      arrowOffsetLeft: 88, //55
      arrowOffsetRight: 240,  //240
      popupOffset: 145
   },
   sel:{ // stores all selectors
      oaNormal: ".open-access-normal",
      oaSupport: ".open-access-optional",
      highlightEl: ".highlight",
      oaPopup: ".oa-popup",
      oaPopupContent: ".oa-popup-content",
      openAccessWrapper: ".open-access",
      arrowBox: ".arrow-box"
   },
   init: function(){
      // sets journals amount
      if ( (jQuery(OpenAccessTable.sel.oaNormal).length > 0) || (jQuery(OpenAccessTable.sel.oaSupport).length > 0) ){
         OpenAccessTable.setJournals();    
      }

      // add popups 
      if (jQuery(OpenAccessTable.sel.oaPopup)){
         OpenAccessTable.makePopups();
      }

      //check highlights
      if (jQuery(OpenAccessTable.sel.openAccessWrapper)){
         OpenAccessTable.columnHighlight();

         // apply lte IE8 fixes
         var iev = OpenAccessTable.getInternetExplorerVersion();
         if (iev <= 8.0){
            OpenAccessTable.ie8Fixes();
         }
      }    
   },

   // Dynamic Data
   setJournals: function(){
      var _self = this;
      var oaAmount = 0;
    
      // Full Open Access    
      jQuery.ajax({
         dataType: "json",
         url: _self.vars.fbResourceUrl,
         success: function(jsonData){
            oaAmount = jsonData.contents.length;
            jQuery(_self.sel.oaNormal).html(oaAmount);    
         }
      });

      // Optional Open Access  
      //jQuery(_self.sel.oaSupport).html(_self.vars.optionalValue);    
   },

   // Column Highlight
   columnHighlight: function(){
      var _self = this;

      // uses jqueryHover plugin
      jQuery('table').tableHover({colClass: 'highlight'});
      jQuery('table').unbind('click').unbind('mouseout');
      jQuery("table").each(function(){
        if (jQuery(this).find("thead").length > 0){ // check thead to find all columns to highlight
          jQuery(this).find("thead").find(_self.sel.highlightEl).each(function(){
             jQuery(this).trigger('mouseover');
          });
        }
        else{ // check first table row to find all columns to highlight
          jQuery(this).find("tr:first").find(_self.sel.highlightEl).each(function(){
            jQuery(this).trigger('mouseover');
          });          
        }
      });
      jQuery('table').unbind('mouseover');
   },
   highlightThisColumn: function(highEl){
       var _self = this;
       var thisIndex = parseInt(highEl.index(),10) + 1;
       highEl.closest("table").find("tr th:nth-child("+thisIndex+")").addClass(_self.vars.highlightClass);
       highEl.closest("table").find("tr td:nth-child("+thisIndex+")").addClass(_self.vars.highlightClass);
   },

   // Popups
   makePopups: function(){
     var _self = this;
     var counter = 0;
     var popupContentObj = null;
     var popupContentHtml = null;

     jQuery(_self.sel.oaPopup).each(function(){
    
        popupContentObj = jQuery(this).next(_self.sel.oaPopupContent);
        popupContentHtml = popupContentObj.html();
        if (popupContentHtml !== undefined){ // means content was found properly
        
           // attach popup content id to popup anchor
           jQuery(this).data("popupid","oa_c_"+counter);       

           // make popup
           var thisClass = "arrow-box";

           var popPos = jQuery(this).position();
           var halfwidth = parseInt(jQuery(this).width(), 10) / 2;

           popPos["top"] = parseInt(popPos["top"], 10) + 30;
           popPos["left"] = parseInt(popPos["left"], 10) + halfwidth;
           popPos["left"] = popPos["left"] - OpenAccessTable.vars.arrowOffsetLeft;
 
           if (jQuery(this).hasClass("oa-popup-right")){ // means this is popup with arrow on the right 160
             thisClass += " arrow-box-right";
             popPos["left"] = popPos["left"] + OpenAccessTable.vars.arrowOffsetLeft - OpenAccessTable.vars.arrowOffsetRight;
           }

           var popupContent = "<div class='"+thisClass+"' style='display:none; left: "+popPos["left"]+"px ; top: "+popPos["top"]+"px ;' id='oa_c_"+counter+"'>";
           popupContent += popupContentHtml;
           popupContent += "</div>";
        
           popupContentObj.remove();
           jQuery(this).after(popupContent);

           OpenAccessTable.attachPopupHandlers(jQuery(this));  
           OpenAccessTable.popupHover(jQuery("#oa_c_"+counter));  
           
           counter++;
        }
        else{ // means content was not found for this element - remove popup class then
           jQuery(this).removeClass("oa-popup");
        }
     });
   },
   attachPopupHandlers: function(thisLink){
       // add intearaction to popups
    thisLink.hover(
        function(e){ // hover in
			
           // show this popup
           jQuery(this).data("open", true);
           thisId = jQuery(this).data("popupid");
           jQuery("#" + thisId).fadeIn();    
        },
        function(){
          var thisId = jQuery(this).data("popupid");        
          thisId = jQuery(this).data("popupid");
          jQuery("#" + thisId).data("visible", true);
          OpenAccessTable.vars.t = setTimeout(function(){
             jQuery("#" + thisId).fadeOut();	
             jQuery("#" + thisId).data("visbile", false);
          }, 700);
        }
    );
   },
   popupHover: function(thisPopup){
	   thisPopup.hover(
         function(){
            clearTimeout(OpenAccessTable.vars.t);
         },
         function(){
           jQuery(this).fadeOut();		
         }
       );
   },
   ie8Fixes: function(){
      // fix rows colors
      jQuery(".open-access table").each(function(){
	     jQuery(this).find("tr:even").addClass("odd");
      });
   },
   getInternetExplorerVersion: function(){
     var rv = 10; // Return value assumes failure.
     if (navigator.appName == 'Microsoft Internet Explorer') {
       var ua = navigator.userAgent;
       var re = new RegExp("MSIE ([0-9]{1,}[\.0-9]{0,})");
       if (re.exec(ua) !== null){
         rv = parseFloat(RegExp.$1);
       }
    }
    return rv;
   }
};

/*
 * Wide template functions
 * Added by lwoollett@squiz.co.uk
 * 12 March 2014
 */


/**
  @name         indexOf js
  @description  indexOf prototype extension for IE8
  @author       mrek
**/
if(!Array.prototype.indexOf){Array.prototype.indexOf=function(e){var t=this.length>>>0;var n=Number(arguments[1])||0;n=n<0?Math.ceil(n):Math.floor(n);if(n<0)n+=t;for(;n<t;n++){if(n in this&&this[n]===e)return n}return-1}} 


/**
  @name          HorNav
  @description   Adds active class to Horizontal nav
  @author        aciesciow
**/
var HorNav = {
   vars:{
    activeClass : "active"
   },
   init: function(){

     if (jQuery("ul.sec_menu").length > 0){
        var navList = jQuery("ul.sec_menu");
        var currentId = navList.data("currentid");
        var thisId = "";
        navList.find("li > a:not(.cta_button)").each(function(){
	       thisId = jQuery(this).data("id") + "";
	       if (thisId.indexOf(currentId) !== -1){
              jQuery(this).addClass(HorNav.vars.activeClass);
           }
        });
     }
   }
};


/**
  @name          ButtonsIe8Fix
  @description   Adds proper classes to buttons to fix n-th child in IE8 
  @author        aciesciow
**/
var ButtonsIe8Fix = {
   sel: {
     newBoxedWrapper: ".nbt",
     buttonsT1Wrapper: ".buttons-box",
     buttonsT2Wrapper: ".buttons-type-two",
     buttonT1: ".button",
     buttonT2: ".boxed-button-2" 
   },
   vars: {
     lastClass: "last",
     class4: "buttons-four",
     class3: "buttons-three",
     class2: "buttons-two"
   },
   init: function(){
      var self = this;
      var newBl = jQuery(self.sel.newBoxedWrapper);

      // buttons type 1
      newBl.find(self.sel.buttonsT1Wrapper).each(function(){
         // 4n
         if (jQuery(this).hasClass(self.vars.class4)){
           jQuery(this).find(self.sel.buttonT1+":nth-child(4n)").addClass(self.vars.lastClass);
         }
         // 3n
         else if (jQuery(this).hasClass(self.vars.class3)){
           jQuery(this).find(self.sel.buttonT1+":nth-child(3n)").addClass(self.vars.lastClass);
         }
         // 2n
         else if (jQuery(this).hasClass(self.vars.class2)){
           jQuery(this).find(self.sel.buttonT1+":nth-child(2n)").addClass(self.vars.lastClass);
         }        
      });

      // buttons type 2
      newBl.find(self.sel.buttonsT2Wrapper).each(function(){
         // 4n
         if (jQuery(this).hasClass(self.vars.class4)){
           jQuery(this).find(self.sel.buttonT2+":nth-child(4n)").addClass(self.vars.lastClass);
         }
         // 3n
         else if (jQuery(this).hasClass(self.vars.class3)){
           jQuery(this).find(self.sel.buttonT2+":nth-child(3n)").addClass(self.vars.lastClass);
         }
         // 2n
         else if (jQuery(this).hasClass(self.vars.class2)){
           jQuery(this).find(self.sel.buttonT2+":nth-child(2n)").addClass(self.vars.lastClass);
         }        
      });
   }
};


/**
  @name          WideSlider
  @description   Functionality of Carousel Box for Wide Content Template
  @author        aciesciow
**/

var WideSlider = {
    vars:{
      defaultBg: "/__data/assets/image/0019/685/small.png",
      pBtnImg: "/__data/assets/image/0003/180822/pause_btn.gif",
      imgTimeout: 9450,
      imgInterval: null
    },
    init: function(){
        $('.wide-slider').each(function (){
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
               slideshowSpeed: 6000,
               useCSS: false,
               directionNav: withArrows,
               controlNav: withBottomNav,
               multipleKeyboard: true,
               animationLoop: loopSlider,
               slideshow: autoSlider,
               start: function(slider){
                  jQuery(".flex-control-paging li a").click(function(){
                     WideSlider.pauseSlider(jQuery(this), slider);
                  });
                  jQuery(".flex-prev, .flex-next").click(function(){
                     slider.play();
                     jQuery(".flex-control-paging li a").removeClass("pause-btn").removeAttr("style");
                     clearInterval(WideSlider.vars.imgInterval);
                  });
                }
           });

           $('.flex-prev, .flex-next').addClass('ir');
        });

        WideSlider.fixNav();        
    },
    fixNav: function(){
        $('.wide-slider .flex-control-nav li a').each(function(){
            $(this).html( '<span>'+ $(this).text() +'</span>' );
        });        
    },
    pauseSlider: function(thisEl, slider){
        if(thisEl.hasClass("pause-btn")){ // means already paused
           slider.play();
           clearInterval(WideSlider.vars.imgInterval);
           thisEl.removeClass("pause-btn").removeAttr("style");
        }
        else{
           slider.pause();
           clearInterval(WideSlider.vars.imgInterval);
           jQuery(".flex-control-paging li a").removeClass("pause-btn").removeAttr("style");

           thisEl.addClass("pause-btn");
           var ts = new Date().getTime();
           var bgImgCss = "url('"+WideSlider.vars.pBtnImg+"?v="+ts+"')";    
           thisEl.css("background-image", bgImgCss);

           WideSlider.reloadGif(thisEl);
        }
    },
    reloadGif: function(thisEl){
        clearInterval(WideSlider.vars.imgInterval);
        var thisElement = thisEl;
        WideSlider.vars.imgInterval = setInterval(function(){
           var ts = new Date().getTime();
           var bgImgCss = "url('"+WideSlider.vars.pBtnImg+"?v="+ts+"')";    
           thisElement.css("background-image", bgImgCss);    
        }, WideSlider.vars.imgTimeout);
    }
};

/* END Wide template functions */

jQuery(document).ready(function(){
   HorNav.init();

    Elsevier.ShowHide.init();
   // Open Access CR related functionalities
   OpenAccessTable.init();
   //Wide template functions
   ButtonsIe8Fix.init();
   WideSlider.init();

});

/* Open Access Table CR end */
