package com.example.barcodeencrypt;

 /*
002:         * Copyright 2003 Sun Microsystems, Inc.  All Rights Reserved.
003:         * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
004:         *
005:         * This code is free software; you can redistribute it and/or modify it
006:         * under the terms of the GNU General Public License version 2 only, as
007:         * published by the Free Software Foundation.  Sun designates this
008:         * particular file as subject to the "Classpath" exception as provided
009:         * by Sun in the LICENSE file that accompanied this code.
010:         *
011:         * This code is distributed in the hope that it will be useful, but WITHOUT
012:         * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
013:         * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
014:         * version 2 for more details (a copy is included in the LICENSE file that
015:         * accompanied this code).
016:         *
017:         * You should have received a copy of the GNU General Public License version
018:         * 2 along with this work; if not, write to the Free Software Foundation,
019:         * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
020:         *
021:         * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa Clara,
022:         * CA 95054 USA or visit www.sun.com if you need additional information or
023:         * have any questions.
024:         */
//        package sun.security.timestamp;

        import java.io.IOException;
        import java.math.BigInteger;
        import java.util.Date;
        import sun.security.util.DerValue;
        import sun.security.util.ObjectIdentifier;
        import sun.security.x509.AlgorithmId;

        /**
036:         * This class provides the timestamp token info resulting from a successful
037:         * timestamp request, as defined in
038:         * <a href="http://www.ietf.org/rfc/rfc3161.txt">RFC 3161</a>.
039:         *
040:         * The timestampTokenInfo ASN.1 type has the following definition:
041:         * <pre>
042:         *
043:         *     TSTInfo ::= SEQUENCE {
044:         *         version                INTEGER  { v1(1) },
045:         *         policy                 TSAPolicyId,
046:         *         messageImprint         MessageImprint,
047:         *           -- MUST have the same value as the similar field in
048:         *           -- TimeStampReq
049:         *         serialNumber           INTEGER,
050:         *          -- Time-Stamping users MUST be ready to accommodate integers
051:         *          -- up to 160 bits.
052:         *         genTime                GeneralizedTime,
053:         *         accuracy               Accuracy                 OPTIONAL,
054:         *         ordering               BOOLEAN             DEFAULT FALSE,
055:         *         nonce                  INTEGER                  OPTIONAL,
056:         *           -- MUST be present if the similar field was present
057:         *           -- in TimeStampReq.  In that case it MUST have the same value.
058:         *         tsa                    [0] GeneralName          OPTIONAL,
059:         *         extensions             [1] IMPLICIT Extensions  OPTIONAL }
060:         *
061:         *     Accuracy ::= SEQUENCE {
062:         *         seconds        INTEGER           OPTIONAL,
063:         *         millis     [0] INTEGER  (1..999) OPTIONAL,
064:         *         micros     [1] INTEGER  (1..999) OPTIONAL  }
065:         *
066:         * </pre>
067:         *
068:         * @since 1.5
069:         * @see Timestamper
070:         * @author Vincent Ryan
071:         */

        public class TimestampToken {

            private int version;
            private ObjectIdentifier policy;
           private BigInteger serialNumber;
           private AlgorithmId hashAlgorithm;
            private byte[] hashedMessage;
            private Date genTime;

            /**
             * Constructs an object to store a timestamp token.
084:             *
085:             * @param status A buffer containing the ASN.1 BER encoding of the
086:             *               TSTInfo element defined in RFC 3161.
087:             */
            public TimestampToken(byte[] timestampTokenInfo) throws IOException {
                if (timestampTokenInfo == null) {
                    throw new IOException("No timestamp token info");
                }
                parse(timestampTokenInfo);
            }

            public BigInteger getSerialNumber(){
                return serialNumber;
            }

            public int getVersion(){
                return version;
            }

            /**
             * Extract the date and time from the timestamp token.
097:             *
098:             * @return The date and time when the timestamp was generated.
099:             */
            public Date getDate() {
               return genTime;
            }

            public AlgorithmId getHashAlgorithm()
            {
                return hashAlgorithm;
            }

            public byte[] getHashedMessage()
            {
                return hashedMessage;
            }
            /*
105:             * Parses the timestamp token info.
106:             *
107:             * @param timestampTokenInfo A buffer containing an ASN.1 BER encoded
108:             *                           TSTInfo.
109:             * @throws IOException The exception is thrown if a problem is encountered
110:             *         while parsing.
111:             */
            private void parse(byte[] timestampTokenInfo) throws IOException {
                DerValue tstInfo = new DerValue(timestampTokenInfo);
               if (tstInfo.tag != DerValue.tag_Sequence) {
                    throw new IOException(
                            "Bad encoding for timestamp token info");
                }
                // Parse version
                version = tstInfo.data.getInteger();

                // Parse policy
                policy = tstInfo.data.getOID();

                // Parse messageImprint
                DerValue messageImprint = tstInfo.data.getDerValue();
                hashAlgorithm = AlgorithmId.parse(messageImprint.data
                        .getDerValue());
                hashedMessage = messageImprint.data.getOctetString();

                // Parse serialNumber
                serialNumber = tstInfo.data.getBigInteger();

                // Parse genTime
                genTime = tstInfo.data.getGeneralizedTime();

                // Parse optional elements, if present
                if (tstInfo.data.available() > 0) {

                    // Parse accuracy
                    // Parse ordering
                    // Parse nonce
                    // Parse tsa
                    // Parse extensions
                }
            }
        }
