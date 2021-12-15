using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Add this to a camera to make it follow an object up to certain limits you define
/// </summary>
public class CameraSystem : MonoBehaviour
{
	private GameObject player;
	public float MinimumX;
	public float MaximumX;
	public float MinimumY;
	public float MaximumY;
	public string ObjectToFollow;

	private void Start()
	{
		player = GameObject.FindGameObjectWithTag(ObjectToFollow);
	}

	private void LateUpdate()
	{
		float x = Mathf.Clamp (player.transform.position.x, MinimumX, MaximumX);
		float y = Mathf.Clamp (player.transform.position.y, MinimumY, MaximumY);
		gameObject.transform.position = new Vector3 (x, y, gameObject.transform.position.z);
	}
}
