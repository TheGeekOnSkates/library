/**
 * Similar to the "Sleep" function in Win32
 * @param {int} ms - The time to sleep, in milliseconds
 */
function sleep(ms)
{
	var start = new Date().getTime();
	for (var i = 0; i < 1e7; i++)
	{
		if ((new Date().getTime() - start) > ms) break;
	}
}