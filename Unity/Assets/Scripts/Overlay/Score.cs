using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour
{
    public Text score;

    void Start()
    {
    }

    void Update()
    {
        PlayerMP1 mp1 = FindObjectOfType<PlayerMP1>();
        if (mp1 != null)
            score.text = mp1.scoreMP1.ToString();
    }
}
