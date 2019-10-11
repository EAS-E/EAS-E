# EAS-E
A partial implementation of Dr. Harry Markowitz's Entity-Attribute-Set-Event language.

Markowitz's originally realized the EAS-E concepts when evolving the discrete-event simulation language SIMSCRIPT. 
Originally a public domain preprocessor to FORTRAN developed at RAND, it became a proprietary product of CACI of which Markowitz was co-founder.

This implementation closely, but not completely, follows the syntax of SIMSCRIPT II.5.
At this time there is no simulation support - Events are not implemented.

This implementation was initiated at the suggestion of Dr. Markowitz and has achieved the goal of implementing a translator of EAS-E to 'C' which is itself written in EAS-E.
It also partially supports the Level 6 concept of seamless persistence of entity instances and set relationships which was realized in great detail by Markowitz, Malhotra and Pazel at IBM.
( ACM Transactions on Database Systems, Vol. 8, No. 4, Dec. 1983, pp 515-542 ).

It also offers an opportunity to explore the concepts of Level 7 - a Language-Writing-Language - by exposing both rule-based syntax definition and 'scripting' of complex language constructs.
( Markowitz, 1979: SIMSCRIPT, In Encylopedia of Computer Science and Technology, Vol. 13, Belzer, Holzman, Kent (eds.) Marcel Dekker, Inc. )

Note: this software makes use of Markup.h/.cpp, a XML utility developed by First Objective Software, Inc.
Please observe their copyright conditions for any commercial use.
