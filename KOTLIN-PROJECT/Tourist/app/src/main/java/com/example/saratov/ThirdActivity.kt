package com.example.saratov

import android.os.Bundle
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity

class ThirdActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_third)

        val backButton = findViewById<Button>(R.id.backButton)
        backButton.setOnClickListener {
            finish() // Закрываем текущую активити и возвращаемся на предыдущую (второй экран)
        }
    }
}