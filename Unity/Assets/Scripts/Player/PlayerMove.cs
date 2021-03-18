using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMove : MonoBehaviour
{
    public CharacterController controller;
    public float walkspeed = 15f;
    Vector3 velocity;
  
    void Update()
    {
        float x = Input.GetAxis("Horizontal");
        float z = Input.GetAxis("Vertical");

        Vector3 move = transform.right * x + transform.forward * z;
        controller.Move(move * walkspeed * Time.deltaTime);
        controller.Move(velocity * walkspeed * Time.deltaTime);
    }
}