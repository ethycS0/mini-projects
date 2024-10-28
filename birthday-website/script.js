const targetDate = new Date(new Date().getFullYear(), 8, 29, 0, 0, 0);
const countdownEl = document.getElementById('countdown');

function updateCountdown() {
    const currentDate = new Date();
    
    const totalSeconds = Math.floor((targetDate - currentDate) / 1000);
    
    if (totalSeconds < 0) {
        countdownEl.innerHTML = "00:00:00";
        return;
    }

    const days = Math.floor(totalSeconds / 3600 / 24);
    const hours = Math.floor((totalSeconds / 3600) % 24);
    const minutes = Math.floor((totalSeconds / 60) % 60);
    const seconds = totalSeconds % 60;

    countdownEl.innerHTML = `${days}d ${hours}h ${minutes}m ${seconds < 10 ? '0' + seconds : seconds}s`;
}

setInterval(updateCountdown, 1000);


