/**
 * Creates a fully accessible mobile-style menu
 * @param {array} l The list of menu items; each menu item should be an
 * object with a "label" (the text users will see), and either a "url"
 * (page the menu item links to) or "code" (function to call when the
 * menu item is clicked).
 * @returns {HTMLElement} A "nav" element containing the entire widget
 * @remarks CSS classes used are: msm-nav, msm-bbn, msm-menu and
 * msm-menuitem
 */
function msmCreate(l) {
	// Set up our variables
	var n = document.createElement('nav'),
		b = document.createElement('button'),
		m = document.createElement('div');
	
	// Set up the navigation region
	n.setAttribute('role', 'navigation');
	n.className = 'msm-nav';
	
	// Set up the button
	b.className = 'msm-btn';
	b.innerHTML = '&#9776;';
	b.setAttribute('aria-label', 'menu');
	b.setAttribute('aria-expanded', 'false');
	b.onclick = _msmOnExpand;
	
	// Set up the menu
	m.className = 'msm-menu';
	m.style.display = 'none';
	m.setAttribute('role', 'menu');
	
	// Set up the menu items
	for (var i=0; i<l.length; i++) {
		var mi = document.createElement('button');
		mi.setAttribute('role', 'menuitem');
		mi.className = 'msm-menuitem';
		mi.innerText = l[i].label;
		if (l[i].url) {
			mi.setAttribute('data-url', l[i].url);
			mi.onclick = _msmOnLink
		}
		else mi.onclick = l[i].code;
		m.appendChild(mi);
	}
	
	// Finish putting together our widget and we're done
	n.appendChild(b);
	n.appendChild(m);
	return n;
}

/**
 * Expands/collapses the mobile-style menu when the user presses the button
 * @param {Event} e An onclick or onkeydown event object
 */
function _msmOnExpand(e) {
	// If expanded, collapse it
	if (e.target.getAttribute('aria-expanded') == 'true') {
		e.target.innerHTML = '&#9776;';
		e.target.setAttribute('aria-expanded', 'false');
		e.target.nextElementSibling.style.display = 'none';
		return;
	}
	// Otherwise, expand it
	e.target.innerHTML = '&#x00D7';
	e.target.setAttribute('aria-expanded', 'true');
	e.target.nextElementSibling.style.display = '';
}

/**
 * Event handler for menu items that just redirect users to other pages
 * @param {Event} e An onclick or onkeydown event object
 */
function _msmOnLink(e) {
	window.location = e.target.getAttribute('data-url');
}
