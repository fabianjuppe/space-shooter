using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreMP1 : MonoBehaviour
{
    public Text scoreMP1Text;
    public GameObject imageVictory;
    public GameObject imageDefeat;


    void Start()
    {
    }

    void Update()
    {
        PlayerMP1 mp1 = FindObjectOfType<PlayerMP1>();
        if (mp1 != null)
        {
            scoreMP1Text.text = mp1.scoreMP1.ToString();
            if (mp1.scoreMP1 <= 0)
            {
                imageVictory.SetActive(true);
                imageDefeat.SetActive(true);
                Time.timeScale = 0f;
            }
        }
    }
}
