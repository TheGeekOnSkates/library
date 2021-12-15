/**
 * A typical US keyboard, emulated in software
 * Its main use would be in emulators and games,
 * where it's important to be able to read the
 * keyboard state in a "main loop".  Obviously,
 * the built-in (event-oriented) way of doing
 * things is better for pretty much everything
 * else, but this much lower-level approach is
 * a decent approximation of reading a hardware
 * device's data directly.
 * 
 * NOTE: To keep the minified JS size down, I
 * used a lot of 1-letter variables.  They all
 * follow these conventions:
 * 		B = byte, b = bit, e = event,
 *		d = data, k = key
 */
namespace Keyboard {

    /**
     * Stores the keyboard state
     */
    let d: Uint8Array;

    /**
     * Updates the keyboard's state on keydown
     * @param e An onkeydown event
     */
    function kd(e: KeyboardEvent) {
        let B = (e.which / 8) | 0, b = 1 << (e.which - (B * 8));
        d[B] |= b;
    }

    /**
     * Updates the keyboard's state on keyup
     * @param e An onkeydown event
     */
    function ku(e: KeyboardEvent) {
        let B = (e.which / 8) | 0, b = 1 << (e.which - (B * 8));
        d[B] &= ~b;
    }

    /**
     * Sets up the keyboard's 
     */
    export function init(): void {
        d = new Uint8Array(32);
        addEventListener("keydown", kd);
        addEventListener("keyup", ku);
    }
    
    /**
     * Reads a single key's state
     * @returns A number > 0 if the key is pressed, or 0 if not
     * @remarks I'm pretty sure most keyboards don't offer this
     * functionality "out of the box", their read() might return
     * the entire array, leaving the programmer to parse it.  But
     * since that's something I'd have to do anyway, I figured I
     * may as well include it here.
     */
    export function read(k: number): number {
		let B = (k / 8) | 0, b = 1 << (k - (B * 8));
        return (d[B] & b);
    }
}

// Test it (this worked)
Keyboard.init();
setInterval(function(){
	if (Keyboard.read(48)) console.log("0 pressed");
	else if (Keyboard.read(70)) console.log("F pressed");
}, 10);
