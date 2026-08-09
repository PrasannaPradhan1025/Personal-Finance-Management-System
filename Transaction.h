#pragma once

#include <string>
enum class TransactionType {
    INCOME,
    EXPENSE
};

class Transaction {
private:
    int id;                
    int userId;               
    double amount;            
    TransactionType type;     
    std::string category;     
    std::string description; 
    std::string date;       
  

public:
   
    Transaction();
    Transaction(int id, int userId, double amount, TransactionType type,std::string category, std::string description, std::string date);

  
    ~Transaction() = default;

 
    int getId() const;
    int getUserId() const;
    double getAmount() const;
    TransactionType getType() const;
    std::string getTypeAsString() const;
    std::string getCategory() const;
    std::string getDescription() const;
    std::string getDate() const;
    


    void setAmount(double amount);
    void setType(TransactionType type);
    void setCategory(const std::string& category);
    void setDescription(const std::string& description);
    void setDate(const std::string& date);
   


};