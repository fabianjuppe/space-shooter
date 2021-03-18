using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Menu : MonoBehaviour
{
    public GameObject menuRoot;
    public GameObject mainCamera;
    private bool keyWasPressed = false;
    public GameObject playerSP;
    public GameObject playerMP1;
    public GameObject playerMP2;

    void Start()
    {
        menuRoot.SetActive(true);
        Time.timeScale = 0f;
        Cursor.lockState = CursorLockMode.Confined;
        Cursor.visible = true;
    }

    void Update()
    {
        //if (Input.GetAxisRaw("Menu") > 0f)
        //{
        //    if (!keyWasPressed)
        //    {
        //        menuRoot.SetActive(!menuRoot.activeSelf);


        //        Time.timeScale = menuRoot.activeSelf ? 0f : 1f;
        //    }

        //    keyWasPressed = true;
        //}
        //else
        //    keyWasPressed = false;
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            if (keyWasPressed == false)
            {
                menuRoot.SetActive(true);
                Time.timeScale = 0.0f;
                //Cursor.lockState = CursorLockMode.None;
                Cursor.lockState = CursorLockMode.Confined;
                Cursor.visible = true;
                keyWasPressed = true;
            }
            else
            {
                Cursor.lockState = CursorLockMode.Locked;
                Cursor.visible = false;
                Time.timeScale = 1.0f;
                menuRoot.SetActive(false);
                keyWasPressed = false;
            }
        }
    }

    public void OnButtonSPPressed()
    {
        Debug.Log("Sinpleplayer...");
        menuRoot.SetActive(false);
        mainCamera.GetComponent<PlayerLook>().enabled = true;
        playerSP.SetActive(true);
        playerMP1.SetActive(false);
        playerMP2.SetActive(false);
        Time.timeScale = 1f;
    }

    public void OnButtonMPPressed()
    {
        Debug.Log("Multiplayer...");
        menuRoot.SetActive(false);
        mainCamera.GetComponent<PlayerLook>().enabled = true;
        playerSP.SetActive(false);
        playerMP1.SetActive(true);
        playerMP2.SetActive(true);
        Time.timeScale = 1f;
    }

    public void OnButtonQuitPressed()
    {
        Debug.Log("Spiel beenden...");
        Application.Quit();
    }
}
