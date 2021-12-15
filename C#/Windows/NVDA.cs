/// <summary>
/// Wraps the NVDA Controller Client DLL.
/// </summary>
public static class NVDA
{
    #region Public fields

    /// <summary>
    /// True if NVDA is currently running, false if not
    /// </summary>
    public static bool IsRunning
    {
        get
        {
            return nvdaController_testIfRunning() == 0;
        }
    }

    #endregion
    #region Public methods

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
        catch (DllNotFoundException)
        {
            // Do nothing or add error handler here
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
        catch (DllNotFoundException)
        {
            // Do nothing or add error handler here
        }
    }

    #endregion
    #region DLL Imports

    [DllImport("nvdaControllerClient32.dll", CharSet = CharSet.Unicode)]
    private static extern int nvdaController_speakText(string text);

    [DllImport("nvdaControllerClient32.dll")]
    private static extern int nvdaController_testIfRunning();

    [DllImport("nvdaControllerClient32.dll")]
    private static extern int nvdaController_cancelSpeech();

    #endregion
}