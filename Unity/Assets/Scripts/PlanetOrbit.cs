using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlanetOrbit : MonoBehaviour
{
    public float rotationSpeed;
    public float dampAmt;
    public bool up = false;
    public bool left = false;
    public bool right = false;

    void Update()
    {
        if(up)
            transform.Rotate((Vector3.up * rotationSpeed) * (Time.deltaTime * dampAmt), Space.Self);    
        else if(right)
            transform.Rotate((Vector3.right * rotationSpeed) * (Time.deltaTime * dampAmt), Space.Self);
        else if(left)
            transform.Rotate((Vector3.left * rotationSpeed) * (Time.deltaTime * dampAmt), Space.Self);
    }
}
