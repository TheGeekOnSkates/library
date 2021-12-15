using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Whatever
{
    /// <summary>
    /// Handles resizing the screen (duh) :D
    /// </summary>
    public class ScreenResizer
    {
        /// <summary>
        /// Passed in the call to spriteBatch.begin(),
        /// This does the actual screen-resizing.
        /// </summary>
        private Matrix Scale;

        /// <summary>
        /// Put this in your game's Initialize method
        /// </summary>
        /// <param name="graphics">The game's graphics object</param>
        /// <param name="TargetWidth">The desired width, in pixels</param>
        /// <param name="TargetHeight">The desired height, in pixels</param>
        public ScreenResizer(GraphicsDeviceManager graphics, float TargetWidth, float TargetHeight)
        {
            float scaleX = (float)graphics.PreferredBackBufferWidth / TargetWidth;
            float scaleY = (float)graphics.PreferredBackBufferHeight / TargetHeight;
            Scale = Matrix.CreateScale(new Vector3(scaleX, scaleY, 1));
        }

        /// <summary>
        /// Put this where you would normally put spriteBatch.Begin
        /// </summary>
        /// <param name="spriteBatch">The SpriteBatch object</param>
        public void StartDraw(SpriteBatch spriteBatch)
        {
            spriteBatch.Begin(SpriteSortMode.Immediate, null, null, null, null, null, Scale);
        }

        /// <summary>
        /// Put this where you would normally put spriteBatch.End
        /// </summary>
        /// <param name="spriteBatch">The SpriteBatch object</param>
        public void EndDraw(SpriteBatch spriteBatch)
        {
            spriteBatch.End();
        }
    }
}
