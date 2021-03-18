using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Bullet : MonoBehaviour
{
    public float expirtyTime = 10f;

    void Start()
    {
        Destroy(gameObject, expirtyTime);
    }

    private void OnCollisionEnter(Collision collision)
    { 
        PlayerMP1 mp1 = collision.gameObject.GetComponent<PlayerMP1>();
        if (mp1 != null)
            mp1.OnHitByBullet();
        PlayerMP2 mp2 = collision.gameObject.GetComponent<PlayerMP2>();
        if (mp2 != null)
            mp2.OnHitByBullet();
        Destroy(gameObject);
    }
}