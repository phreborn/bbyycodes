//###################################################################################################
vector<string> CreateList_HH_non_resonant_kappa_lambda()
{
  vector<string> vector_string_kappa_lambda;

  double epsilon=1e-5;
  //avoid 1

  //better to use double to prevent some clumsy changes of digits

  double step_kappa_lambda=0.2; //this is what there is in the official kappa lambda reweighting
  
  double kappa_lambda=-10;
  
  for (;kappa_lambda<=10;kappa_lambda+=step_kappa_lambda) {
    
    printf("exploring kappa_lambda=%20.20f\n",kappa_lambda);
    
    //    if (kappa_lambda-!=1) {
    if (fabs(kappa_lambda-1.)>epsilon) {
      //      cout << "add the string" << endl;
      vector_string_kappa_lambda.push_back(Return_string_target_kappa(kappa_lambda));
    }
  }

//   //---------------
//   //for tests
//   vector_string_kappa_lambda.push_back(Return_string_target_kappa(4));


  return vector_string_kappa_lambda;
}
//###################################################################################################
string Return_string_target_kappa(double numerical_target_kappa)
{
  bool DEBUG=0;

  if (DEBUG) {
    cout << "====================================" << endl;
    printf("Decode kappa lambda=%20.20f\n",numerical_target_kappa);
  }
  
  double epsilon=1e-5; //to avoid rounding due to representation in power of 2

  string string_target_kappa;
  
  char buffer[1];
  
  if (numerical_target_kappa<0) {
    string_target_kappa+='n';

    numerical_target_kappa=fabs(numerical_target_kappa);
    //change sign to prevent having the sign everywhere
  }
  
  //at this stage, we have absolute number

  if (DEBUG) {
    cout << endl;
    cout << "phase 1" << endl;
    printf("numerical_target_kappa=%20.20f\n",numerical_target_kappa);

    cout << "test >=10" << endl;
  }
  
  if (numerical_target_kappa/10.+epsilon>=1) {
    sprintf(buffer,"%d",(int)(numerical_target_kappa/10.+epsilon));
    
    if (DEBUG) {
      cout << "yes" << endl;
      cout << "buffer=" << buffer << endl;
    }
    string_target_kappa+=buffer;
    numerical_target_kappa-=(int)((numerical_target_kappa/10.+epsilon))*10;
    numerical_target_kappa=fabs(numerical_target_kappa);
  }
  
  if (DEBUG) {
    cout << endl;
    
    printf("numerical_target_kappa=%20.20f\n",numerical_target_kappa);
    cout << "test >=1" << endl;
  }
  
  if (numerical_target_kappa+epsilon>=1) {

    sprintf(buffer,"%d",(int)(numerical_target_kappa+epsilon));
    
    if (DEBUG) {
      cout << "yes" << endl;
      cout << "resulting buffer=" << buffer << endl;
    }
    
    string_target_kappa+=buffer;
    numerical_target_kappa-=((int)(numerical_target_kappa+epsilon));
    numerical_target_kappa=fabs(numerical_target_kappa);
  }
  else
    string_target_kappa+='0';  

  string_target_kappa+='p';
  
  if (DEBUG) {
    cout << "phase 3" << endl;
    printf("numerical_target_kappa=%20.20f\n",numerical_target_kappa);
    
    cout << "test>=0.1" << endl;
  }

  if (numerical_target_kappa+epsilon>=0.1) {
    
    sprintf(buffer,"%01d",(int)(numerical_target_kappa*10.+epsilon));
    
    if (DEBUG) {
      cout << "yes" << endl;
      
      cout << "buffer=" << buffer << endl;
    }
    
    string_target_kappa+=buffer;
  }
  else
    string_target_kappa+='0';
  
  //keep that for sure
  if (string_target_kappa=="n0p0")
    string_target_kappa="0p0";
  
  if (DEBUG) {
    cout << "this gives : " << string_target_kappa << endl;
    cout << "====================================" << endl;
  }
  
  return string_target_kappa;
}
//###################################################################################################
