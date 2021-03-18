using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMP1 : MonoBehaviour
{
    public int scoreMP1;
    public ParticleSystem explosionEffect;

    public void OnHitByBullet()
    {
        scoreMP1--;
        explosionEffect.Play();
    }

    public void OnHitSatellit()
    {
        scoreMP1 += 1;
    }
}
