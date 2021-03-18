using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMP2 : MonoBehaviour
{
    public int scoreMP2;
    public ParticleSystem explosionEffect;

    public void OnHitByBullet()
    {
        scoreMP2--;
        explosionEffect.Play();
    }

    public void OnHitSatellit()
    {
        scoreMP2 += 1;
    }
}

