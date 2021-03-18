using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreMP2 : MonoBehaviour
{
    public Text scoreMP2Text;
    public GameObject imageVictory;
    public GameObject imageDefeat;


    void Start()
    {
    }

    void Update()
    {
        PlayerMP2 mp2 = FindObjectOfType<PlayerMP2>();
        if (mp2 != null)
        {
            scoreMP2Text.text = mp2.scoreMP2.ToString();
            if (mp2.scoreMP2 <= 0)
            {
                imageVictory.SetActive(true);
                imageDefeat.SetActive(true);
                Time.timeScale = 0f;
            }
        }
    }
}
