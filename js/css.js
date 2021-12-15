/**
 * Formats a number as a CSS color string
 * @param {number} x The number to use as a CSS string
 * @return A string in hexadecimal format ("#" + 6 digits)
 */
function css(x) {
	return "#" + ("000000" + (x).toString(16)).substr(-6)
}
