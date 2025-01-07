from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/register')
def register():
    return render_template('register.html')
    
@app.route('/login') 
def login():
    return render_template('login.html')

@app.route('/user')
def profile():
    return render_template('profile.html')

@app.route('/message')
def message():
    return render_template('message.html')