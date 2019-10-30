# EAS-E
A partial implementation of Dr. Harry Markowitz's Entity-Attribute-Set-Event language.

Markowitz originally realized the EAS-E concepts when evolving the discrete-event simulation language SIMSCRIPT. 
Originally a public domain preprocessor to FORTRAN developed at RAND, it was developed into a compiler in its own right.
This implementation closely, but not completely, follows the syntax of SIMSCRIPT II developed at RAND.
A manual for the RAND SIMSCRIPT II language can be downloaded from: https://www.rand.org/pubs/reports/R460.html
This can serve as an introduction the the EAS-E concept. Note that this implementation is not complete.
Refer to EAS-Enotes.txt for a discussion of some differences.

The language evolved, as SIMSCRIPT II.5, to be a proprietary product of CACI of which Markowitz was co-founder.

At this time there is no simulation support - Events are not implemented.

This implementation was initiated at the suggestion of Dr. Markowitz.
It has achieved the goal of implementing a translator of EAS-E to 'C' which is itself written in EAS-E.

It also partially supports the Level 6 concept of seamless persistence of entity instances and set relationships which was realized in great detail by Markowitz, Malhotra and Pazel at IBM.
( ACM Transactions on Database Systems, Vol. 8, No. 4, Dec. 1983, pp 515-542 ).

It also offers an opportunity to explore the concepts of Level 7 - a Language-Writing-Language - by exposing both rule-based syntax definition and 'scripting' of complex language constructs into less complex realizations.
( Markowitz, 1979: SIMSCRIPT, In Encyclopedia of Computer Science and Technology, Vol. 13, Belzer, Holzman, Kent (eds.) Marcel Dekker, Inc. )

The website EAS-E.org offers some discussion of concepts and sample C++ implementation code.

Note: this software makes use of Markup.h/.cpp, a XML utility developed by First Objective Software, Inc.
Please observe their copyright conditions for any commercial use.

This implementation of EAS-E is the work of Dr. Alasdar Mullarney.
