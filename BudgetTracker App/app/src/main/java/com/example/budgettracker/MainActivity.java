package com.example.budgettracker;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;


public class MainActivity extends AppCompatActivity {

    //variables and constants
    public static final String masterPass="123";
    private static final String PREFS_NAME = "Balance";
    private static final String KEY_MY_VALUE = "";

    int balance;
    //lists to display
    TextView SpendingList;
    TextView AmountList;
    TextView BalanceList;

    //input boxes
    EditText Details;
    EditText Amount;
    EditText Balance;

    //storage files
    public static final String SpendingFile = "spending.txt";
    public static final String AmountFile = "amount.txt";
    public static final String AmountLogFile = "amountLog.txt";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        balance=getValue();
        setContentView(R.layout.activity_main);
    }
    public void checkPass(View view){
            EditText inputPass;
            inputPass = (EditText) findViewById(R.id.Password);
            String enteredPass = inputPass.getText().toString();
            if(enteredPass.equals(masterPass))
                setContentView(R.layout.activity_main);
            else
                setContentView(R.layout.login_fail);
    }

    public void displayMainSheet(View view) {
        setContentView(R.layout.main_sheet);
        calculateBalance(view);
        load(view);
    }

    public void displayUpdateBalanceScreen(View view) {

        setContentView(R.layout.update_balance);
    }
    public void save(View v) {
        Details = findViewById(R.id.Details);
        String detailsText = Details.getText().toString();
        Amount = findViewById(R.id.Amount);
        String amountsText = Amount.getText().toString();
        if((!detailsText.equals(""))&&(!amountsText.equals(""))) {
            try (FileOutputStream fos = openFileOutput(SpendingFile, MODE_APPEND);
                 OutputStreamWriter osw = new OutputStreamWriter(fos);
                 BufferedWriter writer = new BufferedWriter(osw)) {

                // Append the text to the file
                writer.write(detailsText+"\n");

            } catch (IOException e) {
                e.printStackTrace();
            }

            try (FileOutputStream fos = openFileOutput(AmountFile, MODE_APPEND);
                 OutputStreamWriter osw = new OutputStreamWriter(fos);
                 BufferedWriter writer = new BufferedWriter(osw)) {

                // Append the text to the file
                writer.write(amountsText+"\n");

            } catch (IOException e) {
                e.printStackTrace();
            }

            try (FileOutputStream fos = openFileOutput(AmountLogFile, MODE_APPEND);
                 OutputStreamWriter osw = new OutputStreamWriter(fos);
                 BufferedWriter writer = new BufferedWriter(osw)) {

                // Append the text to the file
                writer.write(amountsText+"\n");

            } catch (IOException e) {
                e.printStackTrace();
            }

            displayMainSheet(v);
        }
        else
            Toast.makeText(this, "Enter data in both boxes", Toast.LENGTH_SHORT).show();



    }

    public void load(View v) {
        AmountList = findViewById(R.id.AmountList);
        SpendingList = findViewById(R.id.SpendingList);
        BalanceList = findViewById(R.id.BalanceList);

        FileInputStream fis = null;

        try {
            fis = openFileInput(SpendingFile);
            InputStreamReader isr = new InputStreamReader(fis);
            BufferedReader br = new BufferedReader(isr);
            StringBuilder sb = new StringBuilder();
            String text;
            int number=1;
            while ((text = br.readLine()) != null) {
                sb.append(number).append(") ").append(text).append("\n");
                number++;
            }

            SpendingList.setText(sb.toString());

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (fis != null) {
                try {
                    fis.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        try {
            fis = openFileInput(AmountFile);
            InputStreamReader isr = new InputStreamReader(fis);
            BufferedReader br = new BufferedReader(isr);
            StringBuilder sb = new StringBuilder();
            String text;
            int number=1;
            while ((text = br.readLine()) != null) {
                sb.append(number).append(") ").append(text).append("\n");
                number++;
            }
            AmountList.setText(sb.toString());

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (fis != null) {
                try {
                    fis.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        SpendingList.setMovementMethod(new ScrollingMovementMethod());
        AmountList.setMovementMethod(new ScrollingMovementMethod());
        displayBalance(v);
    }

    public void calculateBalance(View view){
        FileInputStream fis = null;
        int totalSpending=0;
        try {
            fis = openFileInput(AmountLogFile);
            InputStreamReader isr = new InputStreamReader(fis);
            BufferedReader br = new BufferedReader(isr);
            String text;
            while ((text = br.readLine()) != null) {
                totalSpending+=Integer.parseInt(text);
            }

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (fis != null) {
                try {
                    fis.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        File filesDir = getFilesDir();
        String amountLogFileName = "amountLog.txt";
        File amountFile = new File(filesDir, amountLogFileName);
        amountFile.delete();
        balance-=totalSpending;
        saveValue(balance);
        }

    public void updateBalance(View view){
        Balance = findViewById(R.id.Balance);
        String updatedBalance = Balance.getText().toString();
        if(!updatedBalance.equals("")) {
            balance = Integer.parseInt(updatedBalance);
            saveValue(balance);
            File filesDir = getFilesDir();
            String amountLogFileName = "amountLog.txt";
            File amountFile = new File(filesDir, amountLogFileName);
            amountFile.delete();
            displayMainSheet(view);
        }
        else
            Toast.makeText(this, "Balance can't be nothing", Toast.LENGTH_SHORT).show();


    }

    public void displayBalance(View view){

        int getBalance = getValue();
        BalanceList.setText(getBalance+"");
    }

    private int getValue() {
        SharedPreferences prefs = getSharedPreferences(PREFS_NAME, Context.MODE_PRIVATE);
        // If the key is not found, a default value of 0 will be returned
        return prefs.getInt(KEY_MY_VALUE, 0);
    }

    private void saveValue(int value) {
        SharedPreferences prefs = getSharedPreferences(PREFS_NAME, Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = prefs.edit();
        editor.putInt(KEY_MY_VALUE, value);
        editor.apply();
    }
    public void resetList(View view) {
        // Obtain the directory where your app can store its private files
        File filesDir = getFilesDir();


        // Create File objects with the correct paths
        File amountLogFile = new File(filesDir, AmountLogFile);
        File spendingFile = new File(filesDir, SpendingFile);
        File amountFile = new File(filesDir, AmountFile);

        // Delete the files
        if ((spendingFile.delete() && amountLogFile.delete()) || (amountFile.delete())) {
            Toast.makeText(this, "Reset Success", Toast.LENGTH_SHORT).show();
        } else {
            Toast.makeText(this, "Reset Fail", Toast.LENGTH_SHORT).show();
        }
    }

    public void displayMainMenu(View view){

        setContentView(R.layout.activity_main);
    }


    public void displayUpdateSheet(View view){

        setContentView(R.layout.update_sheet);
    }

    public void displayLoginScreen(View view){

        setContentView(R.layout.authentication);
    }

    public void exitApplication(View view) {
        finish();
        System.exit(0);
    }
}
