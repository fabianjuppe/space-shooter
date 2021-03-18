using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Satellite : MonoBehaviour
{
    public GameObject satellite;
    public Material satelliteGreen;
    public Material satelliteRed;
    private float waitTime = 10f;
    private float timer = 0.0f;
    private bool active = true;

    private void Update()
    {
        timer += Time.deltaTime;

        if (timer > waitTime)
        {
            timer -= waitTime;
            active = true;
            satellite.GetComponent<MeshRenderer>().material = satelliteGreen;
        }

    }
    private void OnTriggerEnter(Collider other)
    {
        PlayerMP1 mp1 = other.gameObject.GetComponent<PlayerMP1>();
        if (mp1 != null)
            if (active)
            {
                mp1.OnHitSatellit();
                satellite.GetComponent<MeshRenderer>().material = satelliteRed;
                active = false;
            }

        PlayerMP2 mp2 = other.gameObject.GetComponent<PlayerMP2>();
        if (mp2 != null)
        {
            if (active)
            {
                mp2.OnHitSatellit();
                satellite.GetComponent<MeshRenderer>().material = satelliteRed;
                active = false;
            }
        }
    }
}
