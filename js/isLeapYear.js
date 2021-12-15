/**
 * Checks if a year is a leap year
 * @param {number} year The year
 * @returns {boolean} True if it is, false if it isn't
 */
function isLeapYear(year) {
	return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}
