using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMoveMP : MonoBehaviour
{
    public CharacterController controller;
    public float walkspeed = 15f;
    Vector3 velocity;
  
    void Update()
    {
        float x = Input.GetAxis("HorizontalMP");
        float z = Input.GetAxis("VerticalMP");

        Vector3 move = transform.right * x + transform.forward * z;
        controller.Move(move * walkspeed * Time.deltaTime);
        controller.Move(velocity * walkspeed * Time.deltaTime);
    }
}