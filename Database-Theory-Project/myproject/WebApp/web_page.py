"""
    WISHLIST:
        IMMEDIATE:
            Upload files
        NOT:
            Change Current Students redirect
            Implement 'remember me' (not forgot your password?)
            Admin Account?
"""

import sqlite3
import database as adb

from flask import Flask, render_template, request, url_for, redirect, g
#from flask.ext.login import LoginManager, UserMixin, current_user, login_user, logout_user
#from werkzeug import generate_password_hash, check_password_hash

#init stuff
DATABASE = 'SCIP.db'
PORT = 5003
DEBUG = True
app = Flask(__name__)

"""
#
##
###login extension###
login_manager = LoginManager()
login_manager.init_app(app)

class UserNotFoundError(Exception):
    pass

#simple user class, will want to change this
class User(UserMixin):
    '''Simple User class'''
    USERS = {
        # username: password
        'john': 'love mary',
    }

    def __init__(self, id):
        if not id in self.USERS:
            raise UserNotFoundError()
        self.id = id
        self.password = self.USERS[id]

    @classmethod
    def get(self_class, id):
        '''Return user instance of id, return None if not exist'''
        try:
            return self_class(id)
        except UserNotFoundError:
            return None

# Flask-Login use this to reload the user object from the user ID stored in the session
@login_manager.user_loader
def load_user(id):
    return User.get(id)

###
##
#
"""

#################################
#############WEBPAGE#############
#################################

@app.route('/')
def main():
    app.logger.debug('Main page accessed')
    return render_template('index.html')

@app.route('/SCIP')
def choice():
    app.logger.debug('Main page accessed')
    
    return render_template('choice.html')

#
##
###Student pages
@app.route('/Students')
def student():
    return render_template('students.html')

@app.route('/Student/Login', methods=['GET', 'POST'])
def studentLogin():
    error = None
    if request.method == 'POST':
        #valid_login not implemented
        if valid_login(request.form['username'],
                       request.form['password'],
                       True):
            return log_student_in('username') #log in not implemented
        else:
            error = 'Invalid username/password'

    return render_template('studentlogin.html', error=error)

@app.route('/Student/Register', methods=['GET', 'POST'])
def studentRegister():
    error = None
    if request.method == 'POST':
        #valid_login not implemented

        #returns 0 if successful, 1 if username already taken
        #2 if passwords dont match up, 3 if email already taken/invalid
        flag = reg_student(request.form['username'],
                            request.form['password'],
                            request.form['cpassword'],
                            request.form['email'])
        if not flag: #log in not implemented
            return log_employer_in('username')
        elif flag == 1:
            error = 'Invalid username/password'
        elif flag == 2:
            error = 'Invalid e-mail'
        elif flag == 4:
            error = 'E-mail already in use!'

    return render_template('studentregister.html', error=error)


@app.route('/Student/Home')
def studentHome():
    return render_template('studenthome.html')

@app.route('/Student/Search', methods=['GET', 'POST'])
def studentSearch():
	table = []
	if request.method == 'POST':
		return render_template('studentsearch.html')
	else: 
		table = adb.view_jobs()
		print table
		return render_template('studentsearch.html', table=table)

@app.route('/Student/Apply')
def studentApply():
    return 'studentApply'
#
##
###Employee pages

@app.route('/Employers')
def employer():
    return render_template('employers.html')

@app.route('/Employers/Login', methods=['GET', 'POST'])
def employerLogin():
    error = None
    if request.method == 'POST':
        #valid_login not implemented
        if valid_login(request.form['username'],
                       request.form['password'],
                       False):
            return log_employer_in('username') #log in not implemented
        else:
            error = 'Invalid username/password'

    return render_template('employerlogin.html', error=error)
        
@app.route('/Employers/Register', methods=['GET', 'POST'])
def employerRegister():
    error = None
    if request.method == 'POST':
        #valid_login not implemented

        #returns 0 if successful, 1 if username already taken
        #2 if passwords dont match up, 3 if email already taken/invalid
        flag = reg_employer(request.form['username'],
                            request.form['password'],
                            request.form['cpassword'],
                            request.form['email'])
        if not flag: #log in not implemented
            return log_employer_in('username')
        elif flag == 1:
            error = 'Invalid username/password'
        elif flag == 2:
            error = 'Invalid e-mail'
        elif flag == 3:
            error = 'Company already in use!'

    return render_template('employerregister.html', error=error)

@app.route('/Employer/Home')
def employerHome():
    return render_template('employerhome.html')

@app.route('/Employer/EditLogo')
def employerEditLogo():
    return 'employer'
	
@app.route('/Employer/EditInternships', methods=['GET', 'POST'])
def employerEditInt():
	error = None
	if request.method == 'POST':
		flag = editJob(request.form['job_id'])
		
	return render_template('editInternship.html', error=error)

@app.route('/Employer/AddInternships', methods=['GET', 'POST'])
def employerAddInt():
	error = None
	if request.method == 'POST':
		#valid_login not implemented

		#returns 0 if successful, 1 if username already taken
		#2 if passwords dont match up, 3 if email already taken/invalid
		flag = addInt(request.form['type'],
							request.form['description'], 1)
		if not flag: #log in not implemented
			return log_employer_in('username')
		elif flag == 1:
			error = 'Invalid username/password'
		elif flag == 2:
			error = 'Invalid e-mail'
		elif flag == 3:
			error = 'Company already in use!'
	return render_template('AddInternships.html', error=error)
	
def addInt(type, description, cid):
	adb.add_job(type, description, cid)
	
def editJob(job_id):
	adb.editJob(job_id)


def get_db():
    db = getattr(g, '_database', None)
    if db is None:
        db = g._database = connect_to_database()
    return db

@app.teardown_appcontext
def close_connection(exception):
    db = getattr(g, '_database', None)
    if db is not None:
        db.close()

def valid_login(username, password, Student = True):
    return 1

def log_employer_in(username):
    return redirect('/Employer/Home')

def log_student_in(username):
    return redirect('/Student/Home')

#need to check if email is a possible valid email
#need to have some checks on arguments
def reg_employer(name, password, cpassword, email):

    #return 1 if passwords not equal error
    if password != cpassword:
        return 1
    if '@' not in email:
        return 2
    for r in adb.view_company_t(): #companies can't have same name
        if name == r[0]:
            return 3
    
    else:
        return False

    adb.add_company(name, password, email)

def reg_student(name, password, cpassword, email):

    #return 1 if passwords not equal error
    if password != cpassword:
        return 1
    if '@' not in email:
        return 2
    for r in adb.view_company_t(): #students cant have same email
        if email == r[4]:
            return 4
    
    else:
        return False

    adb.add_student(name, password, email)
    
if __name__ == "__main__":
    app.logger.setLevel(0)
    app.run(port=PORT, debug=True)
