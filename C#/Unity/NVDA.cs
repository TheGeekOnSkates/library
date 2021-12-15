using System;
using System.Runtime.InteropServices;

/// <summary>
/// This class wraps the NVDA Controller Client DLL for Unity.
/// Just put the DLL and this script in your Assets folder,
/// then use this class from other scripts (see examples).
/// </summary>
public static class NVDA
{
	/// <summary>
	/// Makes NVDA speak a string of text
	/// </summary>
	/// <param name="text">The text to speak</param>
	/// <example>NVDA.Say("Game Over");</example>
	public static void Say(string text)
	{
		try
		{
			nvdaController_speakText(text);
		}
		catch(DllNotFoundException)
		{
			// Do nothing - this exception will always be thrown in the editor,
		}
	}

	/// <summary>
	/// Makes NVDA stop talking
	/// </summary>
	/// <example>NVDA.Stop()</example>
	public static void Stop()
	{
		try
		{
			nvdaController_cancelSpeech();
		}
		catch(DllNotFoundException)
		{
			// Do nothing - this exception will always be thrown in the editor,
		}
	}

	#region DLL Imports

	[DllImport("Assets\\nvdaControllerClient32.dll", CharSet = CharSet.Unicode)]
	private static extern int nvdaController_speakText(string text);

	[DllImport("Assets\\nvdaControllerClient32.dll")]
	private static extern int nvdaController_cancelSpeech();

	#endregion
}