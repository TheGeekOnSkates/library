// Similar to keyboard.ts, but emulating a speech synthesizer
// far from done
namespace TTS {
    let d: Uint8Array, u: SpeechSynthesisUtterance;

    export function init() {
        d = new Uint8Array(200);
        if (typeof(speechSynthesis) == "undefined") {
            for (let i=0; i<5; i++) d[i] = 255;
        }
        else {
            u = new SpeechSynthesisUtterance();
            let v = speechSynthesis.getVoices();
            d[0] = v.length;
            for (let i=0; i<v.length; i++) if (v[i].default) { d[1] = i; break; }
            d[3] = 50; d[5] = 50; d[5] = 50;
            for (let i=6; i<d.length; i++) d[i] = 0;
        }

        /*
        MEMORY MAP:
            Byte 0: Total voices available (1 to 254).  255 = no Web Speech support
            Byte 1: Currently selected voice (255 = use ARIA)
            Byte 2: The rate (0-100)
            Byte 3: The pitch (0-100)
            Byte 4: The volume (0-100)
            Bytes 5-199: The speech buffer
        */
    }
}
