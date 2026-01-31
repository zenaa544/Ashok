# What Happens When You Type a URL in Your Browser and Press Enter?



---

## 1. User Input and Browser Processing

- User enters a URL (e.g., `https://www.example.com`) and hits Enter.
- The browser checks **cache** (memory, disk, service workers) for a local copy of the requested page.
    - If found and valid, the resource is loaded from cache, skipping the network.
    - If not, the browser initiates a network request.

---

## 2. URL Parsing

- The browser parses the URL to determine:
    - **Protocol:** `http` or `https`
    - **Hostname:** e.g., `www.example.com`
    - **Port:** Default is 80 for HTTP, 443 for HTTPS (unless specified)
    - **Path:** e.g., `/index.html`
    - **Query string** and **fragment** (if any)

---

## 3. DNS Resolution

- The browser (often using the OS) checks the **DNS cache** for the IP of `www.example.com`.
- If not cached, it queries the configured DNS server:
    1. Checks the browser's cache
    2. OS cache
    3. Router cache (if applicable)
    4. ISP or public DNS resolver (like 8.8.8.8)
- The DNS resolver returns the IP address for `www.example.com` (e.g., `93.184.216.34`).

---

## 4. TCP (and TLS for HTTPS) Handshake

- The browser establishes a **TCP connection** to the IP/port (`93.184.216.34:443` for HTTPS).
    - **Three-way handshake:**
        1. SYN → (from client to server)
        2. SYN-ACK ← (from server to client)
        3. ACK → (from client to server)
- For HTTPS:
    - After TCP is established, **TLS handshake** occurs:
        - ClientHello, ServerHello (SSL certificates exchanged)
        - The client validates the server certificate (roots of trust)
        - Encrypted session keys are negotiated.

---

## 5. Routing: Packet's Journey

- Each packet is encapsulated in an IP packet with source and destination IP.
- Sent to default gateway (usually your router).
- **NAT (Network Address Translation) occurs at your router or firewall, modifying the source IP of your outbound packet from your private (e.g., 192.168.x.x) to the router's public IP. When reply packets return, the router reverses the translation and sends them to the correct internal machine.**
- **Layer 2 (Data Link):** Uses MAC addresses to deliver frames within the same local network segment (LAN), forwarding data between devices connected to the same switch.
- **Layer 3 (Network):** Uses IP addresses and routing to forward packets across different networks, determining the next hop to reach the final destination over the internet.
- Routers inspect the destination IP and forward the packet hop-by-hop toward the destination, using routing tables.
- Packets traverse the internet (may go through NAT, multiple ISPs, undersea cables, etc.) to reach the web server’s data center.
---

## 6. HTTP Request

- After connection setup, the browser sends an **HTTP request** (usually a GET request for `/`).
    - HTTP headers are sent, such as: Host, User-Agent, Accept, Cookies, etc.

    ```http
    GET / HTTP/1.1
    Host: www.example.com
    User-Agent: Mozilla/5.0 ...
    ...
    ```

---

## 7. Server Response

- The server receives the request, processes it (may check databases, read files, or run code).
- It builds and sends back an **HTTP response**:
    - Status code (e.g., 200 OK, 404 Not Found)
    - Headers (e.g., Content-Type, Cache-Control)
    - Body (HTML, JSON, images, files, etc.)

---

## 8. Browser Rendering

- The browser receives the HTML and begins parsing.
    - It may initiate **additional requests** for CSS, JavaScript, images, fonts, and other resources as referenced in the HTML.
    - For each resource requested, the DNS resolution, TCP/TLS handshake, and HTTP(S) request/response cycle may repeat as needed.
- The browser constructs the **DOM** (Document Object Model), applies CSS styles, executes JavaScript, and lays out the page.

---

## 9. User Sees the Page

- The final page is displayed in the browser, complete with styles and interactivity provided by CSS and JavaScript.

---

## Sequence Diagram: Journey from Browser to Website

```mermaid
sequenceDiagram
    participant User
    participant Browser
    participant DNS as "DNS Server"
    participant Web as "Web Server"
    User->>Browser: Enter URL & press Enter
    Browser->>DNS: Query for www.example.com
    DNS-->>Browser: Return IP address
    Browser->>Web: TCP/TLS handshake,\nHTTP Request
    Web-->>Browser: HTTP Response (HTML)
    Browser->>Web: More HTTP(S) requests (CSS, JS, Images)
    Web-->>Browser: More responses
    Browser->>User: Render page
 ```   
---

# SDN vs VLAN

## VLAN (Virtual Local Area Network)

- **Definition:** VLANs are a Layer-2 network technology that partitions a physical network (switches) into multiple, logical, isolated broadcast domains.
- **Purpose:** Segmentation, isolation, better management, security on a switch or group of connected switches.
- **How:** By tagging Ethernet frames using IEEE 802.1Q; each port on a switch is assigned to a VLAN.
- **Typical Uses:** Separating departments on the same physical infrastructure (e.g., HR, Finance, Engineering), guest vs. staff WiFi, reducing broadcast domains.

**Key Characteristics:**
- Simple, works at the Ethernet switch level.
- Configuration is mostly manual (though it can be automated somewhat).
- Doesn't “program” the network; mostly static rules.

---

## SDN (Software-Defined Networking)

- **Definition:** SDN is an architectural approach that separates the network’s control plane (decision-making: "where should traffic go?") from the data plane (actual forwarding of packets).
- **Purpose:** Centralized, programmable, dynamic, automated control of networks, often using APIs or controllers.
- **How:** By using an SDN controller (e.g., OpenDaylight, ONOS, RYU) to manage forwarding rules on SDN-enabled switches (like OpenFlow switches).
- **Typical Uses:** Data centers, cloud networks, WAN optimization, network automation, service chaining, fast reconfiguration, multi-tenancy.

**Key Characteristics:**
- Centralized control and programmability; changes can be made network-wide with code or policies.
- Supports virtual networks (could use VLANs, VXLAN, MPLS, etc. underneath).
- Enables advanced networking: traffic engineering, QoS, security, automation.

---

## VLAN vs SDN Comparison Table

| Aspect          | VLAN                               | SDN                                      |
|-----------------|------------------------------------|------------------------------------------|
| Stands for      | Virtual Local Area Network         | Software Defined Networking              |
| Main function   | Segment network on L2              | Centralized, programmable network control|
| Level           | Data link (Layer 2)                | Network architecture (all layers)        |
| Control         | Decentralized/manual (per switch)  | Centralized (controller)                 |
| Isolation       | Yes, at broadcast domain           | Yes, can create any logical topology     |
| Automation      | Limited                            | Extensive (via software/API)             |
| Typical config  | Assign VLAN IDs, port membership   | Write policies, apps, use APIs           |
| Example use     | Separate staff/guest networks      | Rapidly reconfigure network for VMs      |
| Underlying tech | IEEE 802.1Q                        | OpenFlow, NETCONF, REST APIs, etc.       |
| Can use VLANs?  | Is the technology itself           | Can use VLANs or other overlays as tools |

---

## Summary Points

- **VLAN** is a basic network segmentation technology, excellent for separating traffic *within* the same physical network at Layer 2.
- **SDN** is an architectural paradigm—*not* a technology—focused on automation, programmability, and centralized control of networks at all layers.
    - SDN can leverage VLANs as one way to segment traffic, but can also use other methods (like VXLAN, GRE, MPLS, etc.) and dynamically change them as needed.
- **You can deploy VLANs without SDN; SDN can manage VLANs (among many other things).**
- **SDN is about network-wide logic and flexibility; VLAN is about layer-2 segmentation.**

---

## Analogy

- **VLAN:** Like having colored lines on the floor of a warehouse to direct different teams and keep their stuff separate.
- **SDN:** Like having a team leader with a bird’s-eye view and a walkie-talkie, who can change the warehouse layout instantly, instruct teams, and even change where the colored lines go, all by issuing commands.
