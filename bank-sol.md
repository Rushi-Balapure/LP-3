# Assignment 3

## Title
Write a smart contract on a test network, for Bank account of a customer for following
operations:
- Deposit money
- Withdraw Money
- Show balance

## Steps

1. Go to [Remix IDE](https://remix.ethereum.org/).

    ![image](https://github.com/user-attachments/assets/473734af-7376-4c8a-b554-ef083c1e63ed)

2. In the "File Explorer" tab, click the + icon to create a new file. Name the file `Bank.sol`.

    ![image](https://github.com/user-attachments/assets/ac5fb0cd-324f-4066-849c-e5326b8a3c57)

3. Copy the following code into the file

    ```sol
    // SPDX-License-Identifier: MIT
    pragma solidity ^0.8.0;
    
    contract BankAccount {
        address public owner;
        uint256 private balance;
    
        event Deposit(address indexed account, uint256 amount);
        event Withdrawal(address indexed account, uint256 amount);
    
        constructor() {
            owner = msg.sender;
            balance = 0;
        }
    
        modifier onlyOwner() {
            require(msg.sender == owner, "Only the owner can perform this action");
            _;
        }
    
        function deposit() public payable {
            require(msg.value > 0, "Deposit amount must be greater than 0");
            balance += msg.value;
            emit Deposit(msg.sender, msg.value);
        }
    
        function withdraw(uint256 amount) public onlyOwner {
            require(amount > 0, "Withdrawal amount must be greater than 0");
            require(amount <= balance, "Insufficient funds");
            balance -= amount;
            payable(owner).transfer(amount);
            emit Withdrawal(msg.sender, amount);
        }
    
        function getBalance() public view returns (uint256) {
            return balance;
        }
    }
    ```

4. In the left sidebar, click on the Solidity Compiler (the "Compile" tab). Ensure the compiler version is set to `0.8.0` or higher (since we're using `^0.8.0` in the contract).
    
    ![image](https://github.com/user-attachments/assets/f885e83f-1dd1-4642-ad5b-4230ad034c22)
    
    Click the Compile Bank.sol button. If there are no errors, the contract will compile successfully.

5. In the left sidebar, click on the Deploy & Run Transactions tab.

    Set the Environment to Injected Provider. This will connect Remix to MetaMask.
    
    ![image](https://github.com/user-attachments/assets/1ba306fd-42ea-4c4d-b0c5-642ff61c66b0)

    When selected, it will open Metamask and prompt you to connect your account. Make sure you connect the TestNet account only. (I'm currently connected to Sepolia.)

    To get test ETH for your account, go [here](https://cloud.google.com/application/web3/faucet/ethereum/sepolia) to claim 0.05 ETH for free from Google.

    Or you can test it out on the Remix VM itself.

    ![image](https://github.com/user-attachments/assets/3add782c-ca61-419c-b260-53bf8ea322a5)

    Hit Deploy to deploy the contract. Metamask will open to confirm the same.
   
    ![image](https://github.com/user-attachments/assets/5cc574c1-c7ba-4fae-861d-271e957f678b)

7. Interact with the Contract

   Once deployed, you'll see the contract under the "Deployed Contracts" section.

   ![image](https://github.com/user-attachments/assets/0ea27c2f-cfef-4f1d-973b-e942133b32c4)

   You can now interact with the contract using the following functions:
   - Deposit: To deposit Ether, enter an amount in the "Value" field (in ETH), and click deposit.
   - Withdraw: To withdraw Ether, enter the amount (in wei) in the withdraw field, and click withdraw.
   - Get Balance: To check your balance, click the getBalance button.

## Testing

1. Select a test account in Remix VM

![image](https://github.com/user-attachments/assets/23d61f3a-8c57-49da-89aa-32b5277874ff)

2. Select the amount you want to deposit

![image](https://github.com/user-attachments/assets/026016d1-0e44-4f4e-b9c8-5e65e67d53df)

3. Hit Deposit to deposit the amount

![image](https://github.com/user-attachments/assets/e7aabffd-9408-41b1-ae08-7ca49c085f26)

4. Hit Get Balance to view the current balance

![image](https://github.com/user-attachments/assets/f3fdef58-ae43-4253-903d-b940aac2ce76)
