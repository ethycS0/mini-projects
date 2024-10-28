from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
import time

header = '''

  __  __                                                      
 |  \/  |                                    /\               
 | \  / | ___  ___ ___  __ _  __ _  ___     /  \  _   _ _   _ 
 | |\/| |/ _ \/ __/ __|/ _` |/ _` |/ _ \   / /\ \| | | | | | |
 | |  | |  __/\__ \__ \ (_| | (_| |  __/  / ____ \ |_| | |_| |
 |_|  |_|\___||___/___/\__,_|\__, |\___| /_/    \_\__, |\__,_|
                              __/ |                __/ |      
                             |___/                |___/       

'''

print(header)
print("For Instagram: Press 1\n")
print("For Discord: Press 2\n\n")

media = int(input("Enter what social media to use: "))

if media == 1:

    username = input("\nEnter Username:")
    password = input("\nEnter Password:")
    

    message = input("\nYour Message: ")
    mlen = int(len(message))

    user = input("\nEnter Valid Instagram First Name of the Recepient: ")
    
    i=0
    j=0

    m = int(input("\nEnter Number of Iterations of message: "))
                            
    driver = webdriver.Firefox()
    driver.get("https://www.instagram.com")

    time.sleep(3)

    driver.find_element(By.XPATH, "//input[@name='username']").send_keys(username)
    driver.find_element(By.XPATH, "//input[@name='password']").send_keys(password)
    driver.find_element(By.XPATH, "//button[@class='_acan _acap _acas _aj1-']").click()

    time.sleep(10)
    
    try:
        driver.find_element(By.XPATH, "//*[@aria-label='Messenger']").click()

        time.sleep(3)

    except:

        driver.find_element(By.XPATH, "//button[@class='_a9-- _a9_1']").click()

    try:
        driver.find_element(By.XPATH, "//*[@aria-label='Messenger']").click()

        time.sleep(3)

    except:

        driver.find_element(By.XPATH, "//button[@class='_a9-- _a9_1']").click()

    driver.find_element(By.XPATH, "//span[text()='{}']".format(user)).click()

    time.sleep(3)

    box = driver.find_element(By.XPATH, "//*[@aria-describedby='Message']")

    while j < m:
        while i < mlen+1: 
            characters = message[i-1:i]
            box.send_keys(characters)
            i = i+1
        time.sleep(1)
        driver.find_element(By.XPATH, "//*[text()='Send']").click()
        i = 0
        j = j + 1


elif media == 2:

    email = input("\nEnter Email ID: ")
    password = input("\nEnter Password: ")

    message = input("\nYour Message: ")
    mlen = int(len(message))

    m = int(input("\nEnter Number of Iterations of message: "))

    user0 = input("\nEnter Valid Discord Username of the Recepient: ")
    user = user0 + " (direct message)"

    driver = webdriver.Firefox()
    driver.get("https://discord.com/login")

    time.sleep(3)

    driver.find_element(By.XPATH, "//input[@name='email']").send_keys(email)
    driver.find_element(By.XPATH, "//input[@name='password']").send_keys(password)
    driver.find_element(By.XPATH, "//button[@class='marginBottom8-emkd0_ button-1cRKG6 button-ejjZWC lookFilled-1H2Jvj colorBrand-2M3O3N sizeLarge-2xP3-w fullWidth-3M-YBR grow-2T4nbg']").click()

    time.sleep(10)

    try:
        driver.find_element(By.XPATH, "//*[@aria-label='{}']".format(user)).click()
    except:
        driver.find_element(By.XPATH, "//*[@aria-label='unread, {}']".format(user)).click()
    
    box = driver.find_element(By.XPATH, "//*[@aria-label='Message @{}']".format(user0))
    j = 0
    while j < m :
        box.send_keys(message)
        box.send_keys(Keys.ENTER)
        time.sleep(1)
        j = j +1
    

driver.quit()

    
